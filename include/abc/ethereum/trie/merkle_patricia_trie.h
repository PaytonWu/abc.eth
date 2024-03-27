// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_MERKLE_PATRICIA_TRIE
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_MERKLE_PATRICIA_TRIE

#pragma once

#include "merkle_patricia_trie_decl.h"

#include <cassert>

namespace abc::ethereum::trie
{

constexpr
merkle_patricia_trie::merkle_patricia_trie(std::unique_ptr<trie_reader> db_reader) : db_reader_{std::move(db_reader)}
{
    assert(db_reader_ != nullptr);
}

} // namespace abc::ethereum::trie

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_MERKLE_PATRICIA_TRIE
