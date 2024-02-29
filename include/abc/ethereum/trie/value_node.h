// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_VALUE_NODE)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_VALUE_NODE

#pragma once

#include "value_node_decl.h"

#include "hash_flag.h"

namespace abc::ethereum::trie
{

constexpr auto
value_node::cache() const -> hash_flag
{
    return hash_flag{true};
}

constexpr auto
value_node::type() const noexcept -> node_type
{
    return node_type::value_node;
}

constexpr auto
value_node::value() const noexcept -> bytes_view_t
{
    return value_;
}

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_VALUE_NODE
