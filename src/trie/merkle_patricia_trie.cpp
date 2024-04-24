// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/trie/merkle_patricia_trie.h>

#include <abc/ethereum/trie/compact_bytes.h>
#include <abc/ethereum/trie/error.h>
#include <abc/ethereum/trie/full_node.h>
#include <abc/ethereum/trie/hash_node.h>
#include <abc/ethereum/trie/nibble_bytes.h>
#include <abc/ethereum/trie/rlp/node_decode.h>
#include <abc/ethereum/trie/short_node.h>
#include <abc/ethereum/trie/value_node.h>

#include <range/v3/view/enumerate.hpp>

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
        return remove(this->root_, nibble_bytes_view{}, nibble_key).transform([this](auto &&) { return; });
    }

    return insert(this->root_, nibble_bytes_view{}, nibble_key, std::make_shared<value_node>(value)).transform([](auto &&) { return; });
}

auto
merkle_patricia_trie::try_get(bytes_view_t /*key*/) const -> expected<bytes_t, std::error_code>
{
    // return db_->try_get(key);
    return {};
}

auto
merkle_patricia_trie::try_update(bytes_view_t /*key*/, bytes_view_t /*value*/, std::error_code & /*ec*/) -> void
{
    // db_->try_update(key, value, ec);
}

auto
merkle_patricia_trie::insert(std::shared_ptr<node_face> const & node, nibble_bytes_view prefix, nibble_bytes_view key, std::shared_ptr<node_face> const & value)
    -> expected<update_result, std::error_code>
{
    if (node == nullptr)
    {
        // New short node is created and track it in the tracer. The node identifier
        // passed is the path from the root node. Note the valueNode won't be tracked
        // since it's always embedded in its parent.
        // t.tracer.onInsert(prefix);
        return update_result{.node = std::make_shared<short_node>(key, value, hash_flag{}), .dirty = true};
    }

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
                              .transform([&short_node, &branch_node, cpl](auto && result) { branch_node->child(short_node->nibble_keys()[cpl]) = result.node; });
            if (result.is_err())
            {
                return make_unexpected(result.error());
            }

            result = insert(nullptr, prefix + key.first(cpl + 1), key.subview(cpl + 1), value).transform([&branch_node, &key, cpl](auto && result) {
                branch_node->child(key[cpl]) = result.node;
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
            return insert(full_node->child(key.front()), prefix + key.first(1), key.subview(1), value).transform([&node, &full_node, key](auto && result) {
                if (!result.dirty)
                {
                    return update_result{.node = node, .dirty = false};
                }

                auto new_full_node = full_node->clone();
                new_full_node->child(key.front()) = result.node;

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
            assert(hash_node != nullptr);
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
merkle_patricia_trie::remove(std::shared_ptr<node_face> const & node, nibble_bytes_view prefix, nibble_bytes_view key) -> expected<update_result, std::error_code>
{
    if (node == nullptr)
    {
        return update_result{.node = nullptr, .dirty = false};
    }

    switch (node->type())
    {
        case node_type::short_node:
        {
            auto short_node = std::static_pointer_cast<trie::short_node>(node);
            assert(short_node != nullptr);
            auto cpl = common_prefix_length(key, short_node->nibble_keys());

            if (cpl < short_node->nibble_keys().size())
            {
                return update_result{.node = short_node, .dirty = false};
            }

            if (cpl == key.size())
            {
                // The matched short node is deleted entirely and track
                // it in the deletion set. The same the valueNode doesn't
                // need to be tracked at all since it's always embedded.
                // t.tracer.onDelete(prefix)

                return update_result{.node = nullptr, .dirty = true};
            }

            // The key is longer than n.Key. Remove the remaining suffix
            // from the subtrie. Child can never be nil here since the
            // subtrie must contain at least two other values with keys
            // longer than n.Key.

            return remove(short_node->value(), prefix + key.first(short_node->nibble_keys().size()), key.subview(short_node->nibble_keys().size()))
                .transform([&short_node, cpl](auto && result) {
                    if (!result.dirty)
                    {
                        return update_result{.node = short_node, .dirty = false};
                    }

                    switch (result.node->type())
                    {
                        case node_type::short_node:
                        {
                            // The child shortNode is merged into its parent, track
                            // is deleted as well.
                            // t.tracer.onDelete(append(prefix, n.Key...))

                            // Deleting from the subtrie reduced it to another
                            // short node. Merge the nodes to avoid creating a
                            // shortNode{..., shortNode{...}}. Use concat (which
                            // always creates a new slice) instead of append to
                            // avoid modifying n.Key since it might be shared with
                            // other nodes.
                            auto child = std::static_pointer_cast<trie::short_node>(result.node);
                            return update_result{.node = std::make_shared<trie::short_node>(short_node->nibble_keys() + child->nibble_keys(), child->value(), hash_flag{}),
                                                 .dirty = true};
                        }

                        default:
                        {
                            return update_result{.node = std::make_shared<trie::short_node>(short_node->nibble_keys(), result.node, hash_flag{}), .dirty = true};
                        }
                    }
                });
        }

        case node_type::full_node:
        {
            auto full_node = std::static_pointer_cast<trie::full_node>(node);
            return remove(full_node->child(key.front()), prefix + key.first(1), key.subview(1)).transform([&full_node, key](auto && result) {
                if (!result.dirty)
                {
                    return update_result{.node = full_node, .dirty = false};
                }

                auto new_full_node = full_node->clone();
                new_full_node->reset_hash_flag();
                new_full_node->child(key.front()) = result.node;

                // Because n is a full node, it must've contained at least two children
                // before the delete operation. If the new child value is non-nil, n still
                // has at least two children after the deletion, and cannot be reduced to
                // a short node.
                if (result.node != nullptr)
                {
                    return update_result{.node = new_full_node, .dirty = true};
                }

                // Reduction:
                // Check how many non-nil entries are left after deleting and
                // reduce the full node to a short node if only one entry is
                // left. Since n must've contained at least two children
                // before deletion (otherwise it would not be a full node) n
                // can never be reduced to nil.
                //
                // When the loop is done, pos contains the index of the single
                // value that is left in n or -2 if n contains at least two
                // values.
                std::ptrdiff_t pos = -1;
                auto children = new_full_node->children();
                for (auto [i, cld] : ranges::view::enumerate(children))
                {
                    if (cld != nullptr)
                    {
                        if (pos == -1)
                        {
                            pos = static_cast<std::ptrdiff_t>(i);
                        }
                        else
                        {
                            pos = -2;
                            break;
                        }
                    }
                }
                if (pos >= 0)
                {
                    if (pos != 16)
                    {
//                        // If the remaining entry is a short node, it replaces
//                        // n and its key gets the missing nibble tacked to the
//                        // front. This avoids creating an invalid
//                        // shortNode{..., shortNode{...}}.  Since the entry
//                        // might not be loaded yet, resolve it just for this
//                        // check.
//                        auto child = resolve(new_full_node->child(pos).get(), prefix + static_cast<byte>(pos)).transform([](auto && node) { return node; });
//                        if (child->type() == node_type::short_node)
//                        {
//                            // Replace the entire full node with the short node.
//                            // Mark the original short node as deleted since the
//                            // value is embedded into the parent now.
//                            // t.tracer.onDelete(append(prefix, byte(pos)));
//
//                            auto short_node = std::static_pointer_cast<trie::short_node>(child);
//                            nibble_bytes key{static_cast<byte>(pos)};
//                            key += short_node->nidble_keys();
//
//                            return update_result{.node = std::make_shared<trie::short_node>(nibble_bytes{static_cast<byte>(pos)} + short_node->nibble_keys(), short_node->value(), hash_flag{}), .dirty = true};
//                        }
                    }
                    // Otherwise, n is replaced by a one-nibble short node
                    // containing the child.
                    return update_result{.node = std::make_shared<trie::short_node>(nibble_bytes::from<byte_value::nibble>({static_cast<byte>(pos)}).value(), new_full_node->child(pos), hash_flag{}), .dirty = true};
                }
                // n still contains at least two values and cannot be reduced.
                return update_result{.node = new_full_node, .dirty = true};
            });
        }

        case node_type::value_node:
        {
            return update_result{.node = nullptr, .dirty = true};
        }

        case node_type::hash_node:
        {
            auto hash_node = std::static_pointer_cast<trie::hash_node>(node);
            assert(hash_node != nullptr);
            return resolve(hash_node.get(), prefix).and_then([this, prefix, key](auto && node) { return remove(node, prefix, key); });
        }

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
    assert(hash_node != nullptr);

    return db_reader_->node(prefix, hash_node->hash()).transform([hash_node](auto && bytes) { return ethereum::trie::rlp::must_decode_node(hash_node->hash(), bytes); });
}

} // namespace abc::ethereum::trie
