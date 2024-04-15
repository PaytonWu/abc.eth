// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_HASH_NODE
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_HASH_NODE

#pragma once

#include "hash_node_decl.h"

#include "hash_flag.h"

namespace abc::ethereum::trie
{

constexpr
hash_node::hash_node(h256_t const & hash) : hash_{hash}
{
}

constexpr auto
hash_node::cache() const -> hash_flag
{
    return hash_flag{true};
}

constexpr auto
hash_node::type() const noexcept -> node_type
{
    return node_type::hash_node;
}

constexpr auto
hash_node::hash() const noexcept -> h256_t const &
{
    return hash_;
}

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_HASH_NODE
