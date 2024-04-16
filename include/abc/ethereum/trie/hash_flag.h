// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_HASH_FLAG
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_HASH_FLAG

#pragma once

#include "hash_flag_decl.h"

namespace abc::ethereum::trie
{

constexpr hash_flag::hash_flag(h256_t const & hash, bool dirty) : hash_{hash}, dirty_{dirty}
{
}

constexpr hash_flag::hash_flag(h256_t const & hash) : hash_{hash}
{
}

constexpr hash_flag::hash_flag(bool dirty) : dirty_{dirty}
{
}

constexpr auto
hash_flag::hash() const noexcept -> h256_t const &
{
    return hash_;
}

constexpr auto
hash_flag::dirty() const noexcept -> bool
{
    return dirty_;
}

constexpr auto
hash_flag::hash(h256_t const & value) -> void
{
    hash_ = value;
}

constexpr auto
hash_flag::dirty(bool value) -> void
{
    dirty_ = value;
}

constexpr auto
hash_flag::reset() -> void
{
    hash_.clear();
    dirty_ = true;
}

} // namespace abc::ethereum::trie

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_HASH_FLAG
