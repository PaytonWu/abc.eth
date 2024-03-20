// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIE_READER)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIE_READER

#pragma once

#include "trie_reader_decl.h"

#include <cassert>

namespace abc::ethereum::trie
{

constexpr trie_reader::trie_reader(h256_t const & owner, std::unique_ptr<triedb::database_reader> reader)
    : owner_{owner}, reader_{std::move(reader)}
{
    assert(reader_);
}



}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIE_READER
