// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_DATABASE_READER_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_DATABASE_READER_DECL

#pragma once

#include "database_reader_fwd_decl.h"

#include <abc/bytes.h>
#include <abc/expected.h>
#include <abc/fixed_hash.h>

namespace abc::ethereum::trie
{

class database_reader
{
public:
    database_reader() = default;
    database_reader(database_reader const &) = delete;
    database_reader(database_reader &&) = default;
    virtual ~database_reader() = default;

    auto
    operator=(database_reader const &) -> database_reader & = delete;

    auto
    operator=(database_reader &&) -> database_reader & = default;

    [[nodiscard]] virtual auto
    node(h256_t const & owner, h256_t const & hash, bytes_view_t path) const -> expected<bytes_t, std::error_code> = 0;
};

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_DATABASE_READER_DECL
