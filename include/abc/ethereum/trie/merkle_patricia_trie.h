// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_MERKLE_PATRICIA_TRIE
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_MERKLE_PATRICIA_TRIE

#pragma once

#include "merkle_patricia_trie_decl.h"

#include "error.h"
#include "full_node.h"
#include "hash_node.h"
#include "nibble_bytes.h"
#include "nibble_bytes_view.h"
#include "short_node.h"
#include "value_node.h"

#include <cassert>

namespace abc::ethereum::trie
{

template <typename DbReaderT>
merkle_patricia_trie<DbReaderT>::merkle_patricia_trie(DbReaderT * dbReader) : dbReader_{dbReader}
{
    assert(dbReader_ != nullptr);
}

template <typename DbReaderT>
auto
merkle_patricia_trie<DbReaderT>::hash() const -> h256_t
{
    // return db_->hash();
    return {};
}

template <typename DbReaderT>
auto
merkle_patricia_trie<DbReaderT>::get(bytes_view_t key) const -> expected<bytes_t, std::error_code>
{
    if (committed_)
    {
        return make_unexpected(make_error_code(errc::trie_already_committed));
    }

    return try_get(key);
}

template <typename DbReaderT>
auto
merkle_patricia_trie<DbReaderT>::update(bytes_view_t key, bytes_view_t value) -> expected<void, std::error_code>
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

    return insert(this->root_, nibble_bytes_view{}, nibble_key, value);
}

template <typename DbReaderT>
auto
merkle_patricia_trie<DbReaderT>::try_get(bytes_view_t key) const -> expected<bytes_t, std::error_code>
{
    // return db_->try_get(key);
    return {};
}

template <typename DbReaderT>
auto
merkle_patricia_trie<DbReaderT>::try_update(bytes_view_t key, bytes_view_t value, std::error_code & ec) -> void
{
    // db_->try_update(key, value, ec);
}

template <typename DbReaderT>
auto
merkle_patricia_trie<DbReaderT>::insert(std::shared_ptr<node_face> const & node, nibble_bytes_view prefix, nibble_bytes_view key, bytes_view_t value)
    -> expected<update_result, std::error_code>
{
    if (key.empty())
    {
        if (node->type() == node_type::value_node && std::static_pointer_cast<value_node>(node)->value() == value)
        {
            return update_result{.node = node, .dirty = false};
        }

        return update_result{.node = std::make_shared<value_node>(value), .dirty = true};
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
                auto insert_result = insert(short_node->value(), prefix + key.first(cpl), new_key, value);

                return insert_result.and_then([&](update_result & result) {
                    if (!result.dirty)
                    {
                        return update_result{.node = short_node, .dirty = false};
                    }

                    return update_result{.node = std::make_shared<trie::short_node>(short_node->nibble_keys(), result.node, hash_flag{}), .dirty = true};
                });
            }
            // Otherwise branch out at the index where they differ.
            auto branch_node = std::make_shared<trie::full_node>();
            auto insert_result = insert(nullptr, prefix + short_node->nibble_keys().first(cpl + 1), short_node->nibble_keys().subview(cpl + 1), short_node->value());
            if (insert_result.is_err())
            {
                return insert_result;
            }
            branch_node->children(short_node->nibble_keys()[cpl]) = insert_result.node;

            insert_result = insert(nullptr, prefix + key.first(cpl + 1), key.subview(cpl + 1), value);
            if (insert_result.is_err())
            {
                return insert_result;
            }
            branch_node->children(key[cpl]) = insert_result.node;

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
            auto insert_result = insert(full_node->children(key.front()), prefix + key.first(1), key.subview(1), value);
            insert_result
                .and_then([&full_node, key](update_result & result) {
                    if (!result.dirty)
                    {
                        return update_result{.node = full_node, .dirty = false};
                    }

                    auto new_full_node = std::make_shared<trie::full_node>(*full_node);
                    new_full_node->children(key.front()) = result.node;

                    return update_result{.node = new_full_node, .dirty = true};
                })
                .or_else([&full_node](std::error_code const & ec) { return update_result{.node = full_node, .dirty = false}; });
            break;
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
            rn, err := t.resolve(n, prefix)
                            if err != nil {
                                          return false, nil, err
                                      }
                        dirty, nn, err := t.insert(rn, prefix, key, value)
                                    if !dirty || err != nil {
                return false, rn, err
            }
            return true, nn, nil
            break;
        }

        default:
        {
            break;
        }
    }
    return {};
}

template <typename DbReaderT>
auto
merkle_patricia_trie<DbReaderT>::resolve(trie::hash_node * hash_node, abc::ethereum::trie::nibble_bytes_view prefix) -> expected<std::shared_ptr<node_face>, std::error_code>
{
    dbReader_->node(prefix, hash_node->hash());

}

} // namespace abc::ethereum::trie

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_MERKLE_PATRICIA_TRIE
