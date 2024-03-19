// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIEDB_HASHDB_DATABASE_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIEDB_HASHDB_DATABASE_DECL

#pragma once

#include "database_fwd_decl.h"

#include <abc/bytes.h>
#include <abc/fixed_hash.h>
#include <abc/expected.h>

#include <memory>
#include <system_error>
#include <unordered_map>

namespace abc::ethereum::trie::triedb::hashdb
{

template <typename DatabaseT>
class database
{
private:
    std::unique_ptr<DatabaseT> database_;
    std::unordered_map<h256_t, bytes_t> cleans_;
    std::unordered_map<h256_t, bytes_t> dirties_;

public:
    database() = delete;
    database(database const &) = delete;
    database(database &&) = default;
    ~database() = default;

    auto
    operator=(database const &) -> database & = delete;

    auto
    operator=(database &&) -> database & = default;

    database(std::unique_ptr<DatabaseT> database);

public:
    auto
    insert(h256_t const & hash, bytes_t node) -> void;

    auto
    node(h256_t const & hash) const -> expected<bytes_t, std::error_code>;

    auto
    commit(h256_t const & root) -> expected<void, std::error_code>;
};

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIEDB_HASHDB_DATABASE_DECL
