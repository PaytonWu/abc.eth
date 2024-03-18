// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIEDB_HASHDB_DATABASE)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIEDB_HASHDB_DATABASE

#pragma once

#include "database_decl.h"

namespace abc::ethereum::trie::triedb::hashdb
{

template <typename DatabaseT>
auto
database<DatabaseT>::node(h256_t const & hash) const -> expected<bytes_t, std::error_code>
{
    if (hash.empty())
    {
        return make_unexpected(std::make_error_code(std::errc::invalid_argument)
    }

    if (auto const it = cleans_.find(hash); it != cleans_.end())
    {
        // memcacheCleanHitMeter.Mark(1);
        // memcacheCleanReadMeter.Mark(int64(len(enc)));
        return it->second;
    }

    if (auto const it = dirties_.find(hash); it != dirties_.end())
    {
        // memcacheDirtyHitMeter.Mark(1);
        // memcacheDirtyReadMeter.Mark(int64(len(enc)));
        return it->second;
    }

    auto encoded_value = database_->node(hash);
    if (!encoded_value.empty())
    {
        // memcacheCleanMissMeter.Mark(1);
        // memcacheCleanReadMeter.Mark(int64(len(enc)));
        cleans_.emplace(hash, encoded_value);
        return encoded_value;
    }

    return make_unexpected(std::make_error_code(std::errc::no_such_file_or_directory));
}

} // namespace abc::ethereum::trie::triedb::hashdb

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIEDB_HASHDB_DATABASE
