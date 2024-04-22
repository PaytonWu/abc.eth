// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_BYTE_VALUE_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_BYTE_VALUE_DECL

#pragma once

#include "byte_value_fwd_decl.h"

namespace abc::ethereum::trie
{

enum class byte_value : std::uint8_t
{
    nibble = 0,
    raw = 1,
};

} // namespace abc::ethereum::trie

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_BYTE_VALUE_DECL
