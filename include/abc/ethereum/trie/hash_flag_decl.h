// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_HASH_FLAG_DECL
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_HASH_FLAG_DECL

#pragma once

#include "hash_flag_fwd_decl.h"

#include <abc/fixed_hash.h>

namespace abc::ethereum::trie
{

class hash_flag
{
private:
    h256_t hash_{};
    bool dirty_{false};

public:
    hash_flag() = default;

    constexpr hash_flag(h256_t const & hash, bool dirty);
    constexpr explicit hash_flag(h256_t const & hash);
    constexpr explicit hash_flag(bool dirty);

    constexpr auto
    hash() const noexcept -> h256_t const &;

    [[nodiscard]] constexpr auto
    dirty() const noexcept -> bool;

    constexpr auto
    hash(h256_t const & value) -> void;

    constexpr auto
    dirty(bool value) -> void;
};

} // namespace abc::ethereum::trie

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_HASH_FLAG_DECL
