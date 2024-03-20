// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIE_READER_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIE_READER_DECL

#pragma once

#include "trie_reader_fwd_decl.h"

#include "nibble_bytes_view_decl.h"
#include "triedb/database_reader_decl.h"

#include <abc/fixed_hash.h>

#include <memory>

namespace abc::ethereum::trie
{

class trie_reader
{
    h256_t owner_;
    std::unique_ptr<triedb::database_reader> reader_;

public:
    trie_reader() = delete;
    trie_reader(trie_reader const &) = delete;
    trie_reader(trie_reader &&) = default;
    ~trie_reader() = default;

    auto
    operator=(trie_reader const &) -> trie_reader & = delete;

    auto
    operator=(trie_reader &&) -> trie_reader & = default;

    constexpr trie_reader(h256_t const & owner, std::unique_ptr<triedb::database_reader> reader);

    [[nodiscard]] auto
    node(nibble_bytes_view path, h256_t const & hash) const -> expected<bytes_t, std::error_code>;
};

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIE_READER_DECL
