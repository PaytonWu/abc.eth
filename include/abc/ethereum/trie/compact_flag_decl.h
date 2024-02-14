// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_COMPACT_FLAG_DECL
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_COMPACT_FLAG_DECL

#pragma once

#include "compact_flag_fwd_decl.h"

namespace abc::ethereum::trie
{

enum class compact_flag : abc::byte
{
    extension_even = 0x00,
    odd = 0x01,
    extension_odd = odd,
    leaf = 0x02,
    leaf_even = leaf,
    leaf_odd = leaf | odd,
};

constexpr auto
operator&(compact_flag lhs, compact_flag rhs) noexcept -> compact_flag;

constexpr auto
operator|(compact_flag lhs, compact_flag rhs) noexcept -> compact_flag;

[[nodiscard]] constexpr auto
odd(abc::ethereum::trie::compact_flag flag) noexcept -> bool;

[[nodiscard]] constexpr auto
even(abc::ethereum::trie::compact_flag flag) noexcept -> bool;

[[nodiscard]] constexpr auto
extension(abc::ethereum::trie::compact_flag flag) noexcept -> bool;

[[nodiscard]] constexpr auto
leaf(abc::ethereum::trie::compact_flag flag) noexcept -> bool;

} // namespace abc::ethereum::trie

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_COMPACT_FLAG_DECL
