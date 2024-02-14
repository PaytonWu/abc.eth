// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_COMPACT_FLAG
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_COMPACT_FLAG

#pragma once

#include "compact_flag_decl.h"

namespace abc::ethereum::trie
{

constexpr auto
operator&(compact_flag const lhs, compact_flag const rhs) noexcept -> compact_flag
{
    return static_cast<compact_flag>(static_cast<abc::byte>(lhs) & static_cast<abc::byte>(rhs));
}

constexpr auto
operator|(compact_flag const lhs, compact_flag const rhs) noexcept -> compact_flag
{
    return static_cast<compact_flag>(static_cast<abc::byte>(lhs) | static_cast<abc::byte>(rhs));
}

constexpr auto
odd(abc::ethereum::trie::compact_flag flag) noexcept -> bool
{
    return (flag & compact_flag::odd) == compact_flag::odd;
}

constexpr auto
even(abc::ethereum::trie::compact_flag flag) noexcept -> bool
{
    return !odd(flag);
}

constexpr auto
extension(abc::ethereum::trie::compact_flag flag) noexcept -> bool
{
    return !leaf(flag);
}

constexpr auto
leaf(abc::ethereum::trie::compact_flag flag) noexcept -> bool
{
    return (flag & compact_flag::leaf) == compact_flag::leaf;
}

} // namespace abc::ethereum::trie

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_COMPACT_FLAG
