// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIEDB_HASHDB_DATABASE_READER)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIEDB_HASHDB_DATABASE_READER

#pragma once

#include "database_reader_decl.h"

namespace abc::ethereum::trie::triedb::hashdb
{

template <typename PersistentDBT>
auto
database_reader<PersistentDBT>::node(h256_t const & owner, h256_t const & hash, nibble_bytes_view path) const -> expected<bytes_t, std::error_code>
{
    return database_.node(hash);
}

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIEDB_HASHDB_DATABASE_READER
