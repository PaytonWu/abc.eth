// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIE_READER_FWD_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIE_READER_FWD_DECL

#pragma once

namespace abc::ethereum::trie
{

// trie_reader is a wrapper of the underlying node reader. It's not safe
// for concurrent usage.
class [[nodiscard]] trie_reader;

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIE_READER_FWD_DECL
