// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_MERKLE_PATRICIA_TRIE
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_MERKLE_PATRICIA_TRIE

#pragma once

#include "error.h"
#include "merkle_patricia_trie_decl.h"

#include <cassert>

namespace abc::ethereum::trie
{

template <typename TrieDbT>
merkle_patricia_trie<TrieDbT>::merkle_patricia_trie(TrieDbT * db)
    : db_(db)
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
merkle_patricia_trie<TrieDbT>::update(bytes_view_t key, bytes_view_t value, std::error_code & ec) -> void
{
    if (committed_)
    {
        ec = make_error_code(errc::trie_already_committed);
        return;
    }

    if (value.empty())
    {
        remove(key, ec);
    }
    else
    {
        insert(key, value, ec);
    }
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



}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_MERKLE_PATRICIA_TRIE
