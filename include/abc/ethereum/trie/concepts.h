// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_CONCEPTS
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_CONCEPTS

#pragma once

#include <abc/ethereum/rlp/sbuffer.h>

#include <abc/bytes.h>
#include <abc/fixed_hash.h>

#include <concepts>
#include <tuple>

namespace abc::ethereum::trie
{

template <typename T>
concept trie_node = requires(T const t, rlp::sbuffer & buffer, std::string_view indent)
{
    { t.cache() } -> std::same_as<std::tuple<h256_t, bool>>;
    { t.encode(buffer) } -> std::same_as<void>;
    { t.fstring(indent) } -> std::same_as<std::string>;
};

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_CONCEPTS
