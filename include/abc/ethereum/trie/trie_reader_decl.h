// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIE_READER_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIE_READER_DECL

#pragma once

#include "trie_reader_fwd_decl.h"

#include "database_reader_decl.h"

#include <abc/fixed_hash.h>

#include <memory>

namespace abc::ethereum::trie
{

class trie_reader
{
    h256_t owner_;
    std::unique_ptr<database_reader> reader_;

public:

};

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIE_READER_DECL
