// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "abc/ethereum/trie/merkle_patricia_trie.h"

namespace abc::ethereum::trie
{

auto
merkle_patricia_trie::hash() const -> h256_t
{
    // return db_->hash();
    return {};
}

auto
merkle_patricia_trie::get(bytes_view_t key) const -> expected<bytes_t, std::error_code>
{
    if (committed_)
    {
        return make_unexpected(make_error_code(errc::trie_already_committed));
    }

    return try_get(key);
}

auto
merkle_patricia_trie::update(bytes_view_t key, bytes_view_t value) -> expected<void, std::error_code>
{
    if (committed_)
    {
        return make_unexpected(make_error_code(errc::trie_already_committed));
    }

    auto nibble_key = nibble_bytes::from(key);
    if (value.empty())
    {
        return remove(key);
    }

    return insert(this->root_, nibble_bytes_view{}, nibble_key, std::make_shared<value_node>(value)).transform([](auto &&) { return; });
}

auto
merkle_patricia_trie::try_get(bytes_view_t key) const -> expected<bytes_t, std::error_code>
{
    // return db_->try_get(key);
    return {};
}

auto
merkle_patricia_trie::try_update(bytes_view_t key, bytes_view_t value, std::error_code & ec) -> void
{
    // db_->try_update(key, value, ec);
}

auto
merkle_patricia_trie::insert(std::shared_ptr<node_face> const & node, nibble_bytes_view prefix, nibble_bytes_view key, std::shared_ptr<node_face> const & value)
    -> expected<update_result, std::error_code>
{
    if (key.empty())
    {
        if (node->type() == node_type::value_node && value->type() == node_type::value_node &&
            std::static_pointer_cast<value_node>(node)->value() == std::static_pointer_cast<value_node>(value)->value())
        {
            return update_result{.node = node, .dirty = false};
        }

        return update_result{.node = value, .dirty = true};
    }

    switch (node->type())
    {
        case node_type::short_node:
        {
            auto short_node = std::static_pointer_cast<trie::short_node>(node);
            auto cpl = common_prefix_length(key, short_node->nibble_keys());

            // If the whole key matches, keep this short node as is
            // and only update the value.
            if (cpl == short_node->nibble_keys().size())
            {
                auto new_key = key.subview(cpl);
                return insert(short_node->value(), prefix + key.first(cpl), new_key, value).transform([&short_node, new_key](auto && result) {
                    if (!result.dirty)
                    {
                        return update_result{.node = short_node, .dirty = false};
                    }

                    return update_result{.node = std::make_shared<trie::short_node>(new_key, result.node, hash_flag{}), .dirty = true};
                });
            }
            // Otherwise branch out at the index where they differ.
            auto branch_node = std::make_shared<trie::full_node>();
            auto result = insert(nullptr, prefix + short_node->nibble_keys().first(cpl + 1), short_node->nibble_keys().nibbles_view(cpl + 1), short_node->value())
                              .transform([&short_node, &branch_node, cpl](auto && result) { branch_node->children(short_node->nibble_keys()[cpl]) = result.node; })
                              .transform([this, prefix, key, &value, &branch_node, cpl]() {
                                  insert(nullptr, prefix + key.first(cpl + 1), key.subview(cpl + 1), value).transform([&branch_node, &key, cpl](auto && result) {
                                      branch_node->children(key[cpl]) = result.node;
                                  });
                              });
            if (result.is_err())
            {
                return make_unexpected(result.error());
            }

            // Replace this shortNode with the branch if it occurs at index 0.
            if (cpl == 0)
            {
                return update_result{.node = branch_node, .dirty = true};
            }

            // New branch node is created as a child of the original short node.
            // Track the newly inserted node in the tracer. The node identifier
            // passed is the path from the root node.
            // t.tracer.onInsert(append(prefix, key[:matchlen]...))

            // Replace it with a short node leading up to the branch.
            return update_result{.node = std::make_shared<trie::short_node>(key.first(cpl), branch_node, hash_flag{}), .dirty = true};
        }

        case node_type::full_node:
        {
            auto full_node = std::static_pointer_cast<trie::full_node>(node);
            return insert(full_node->children(key.front()), prefix + key.first(1), key.subview(1), value).transform([&node, &full_node, key](auto && result) {
                if (!result.dirty)
                {
                    return update_result{.node = node, .dirty = false};
                }

                auto new_full_node = full_node->clone();
                new_full_node->children(key.front()) = result.node;

                return update_result{.node = new_full_node, .dirty = true};
            });
        }

        case node_type::invalid:
        {
            // New short node is created and track it in the tracer. The node identifier
            // passed is the path from the root node. Note the valueNode won't be tracked
            // since it's always embedded in its parent.
            // t.tracer.onInsert(prefix)

            return update_result{.node = std::make_shared<short_node>(key, value, hash_flag{}), .dirty = true};
        }

        case node_type::hash_node:
        {
            // We've hit a part of the trie that isn't loaded yet. Load
            // the node and insert into it. This leaves all child nodes on
            // the path to the value in the trie.
            auto hash_node = std::static_pointer_cast<trie::hash_node>(node);
            return resolve(hash_node.get(), prefix).and_then([this, prefix, key, &value](auto && node) { return insert(node, prefix, key, value); });
        }

        case node_type::value_node:
            [[fallthrough]];
        default:
        {
            assert(false);
            unreachable();
            break;
        }
    }
}

auto
merkle_patricia_trie::resolve(trie::hash_node * hash_node, abc::ethereum::trie::nibble_bytes_view prefix) -> expected<std::shared_ptr<node_face>, std::error_code>
{
    assert(db_reader_ != nullptr);
    auto result = db_reader_->node(prefix, hash_node->hash());
}

} // namespace abc::ethereum::trie
