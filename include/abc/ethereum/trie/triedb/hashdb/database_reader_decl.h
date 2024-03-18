// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIEDB_HASHDB_DATABASE_READER_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIEDB_HASHDB_DATABASE_READER_DECL

#pragma once

#include "database_reader_fwd_decl.h"
#include "database_decl.h"

#include <abc/ethereum/trie/triedb/database_reader_decl.h>

namespace abc::ethereum::trie::triedb::hashdb
{

template <typename PersistentDBT>
class database_reader : public abc::ethereum::trie::triedb::database_reader
{
private:
    database<PersistentDBT> database_;

public:
    database_reader() = delete;
    database_reader(database_reader const &) = delete;
    database_reader(database_reader &&) = default;
    ~database_reader() override = default;

    auto
    operator=(database_reader const &) -> database_reader & = delete;

    auto
    operator=(database_reader &&) -> database_reader & = default;

    database_reader(database<PersistentDBT> database);

    [[nodiscard]] auto
    node(h256_t const & owner, h256_t const & hash, bytes_view_t path) const -> expected<bytes_t, std::error_code> override;
};

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIEDB_HASHDB_DATABASE_READER_DECL
