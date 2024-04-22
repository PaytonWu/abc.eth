// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_BYTE_VALUE_TYPE_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_BYTE_VALUE_TYPE_DECL

#pragma once

#include "byte_value_type_fwd_decl.h"

namespace abc::ethereum::trie
{

template <byte_value ByteValue>
struct byte_value_type
{
    static constexpr auto value = ByteValue;
};

} // namespace abc::ethereum::trie

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_BYTE_VALUE_TYPE_DECL
