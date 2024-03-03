// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_MERKLE_PATRICIA_TRIE
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_MERKLE_PATRICIA_TRIE

#pragma once

#include "error.h"
#include "merkle_patricia_trie_decl.h"
#include "nibble_bytes.h"
#include "nibble_bytes_view.h"
#include "value_node.h"
#include "short_node.h"

#include <cassert>

namespace abc::ethereum::trie
{

template <typename TrieDbT>
merkle_patricia_trie<TrieDbT>::merkle_patricia_trie(TrieDbT * db) : db_(db)
{
    assert(db_ != nullptr);
}

template <typename TrieDbT>
auto
merkle_patricia_trie<TrieDbT>::hash() const -> h256_t
{
    // return db_->hash();
    return {};
}

template <typename TrieDbT>
auto
merkle_patricia_trie<TrieDbT>::get(bytes_view_t key) const -> expected<bytes_t, std::error_code>
{
    if (committed_)
    {
        return make_unexpected(make_error_code(errc::trie_already_committed));
    }

    return try_get(key);
}

template <typename TrieDbT>
auto
merkle_patricia_trie<TrieDbT>::update(bytes_view_t key, bytes_view_t value) -> expected<void, std::error_code>
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

template <typename TrieDbT>
auto
merkle_patricia_trie<TrieDbT>::try_get(bytes_view_t key) const -> expected<bytes_t, std::error_code>
{
    // return db_->try_get(key);
    return {};
}

template <typename TrieDbT>
auto
merkle_patricia_trie<TrieDbT>::try_update(bytes_view_t key, bytes_view_t value, std::error_code & ec) -> void
{
    // db_->try_update(key, value, ec);
}

template <typename TrieDbT>
auto
merkle_patricia_trie<TrieDbT>::insert(std::shared_ptr<node_face> & node, nibble_bytes_view prefix, nibble_bytes_view key, bytes_view_t value)
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

                if (insert_result.is_err())
                {
                    return insert_result;
                }

                if (!insert_result.value().dirty)
                {
                    return update_result{.node = short_node, .dirty = false};
                }

                return update_result{.node = std::make_shared<trie::short_node>(short_node->nibble_keys(), insert_result.value(), hash_flag{}), .dirty = true};
            }
            // Otherwise branch out at the index where they differ.

            break;
        }

        case node_type::full_node:
        {
            break;
        }

        case node_type::hash_node:
        {
            break;
        }

        default:
        {
            break;
        }
    }
    return {};
}

} // namespace abc::ethereum::trie

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_MERKLE_PATRICIA_TRIE
