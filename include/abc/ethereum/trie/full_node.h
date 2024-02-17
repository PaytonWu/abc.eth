// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_FULL_NODE)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_FULL_NODE

#pragma once

#include "full_node_decl.h"

namespace abc::ethereum::trie
{

constexpr auto
full_node::type() const noexcept -> node_type
{
    return node_type::full;
}

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_FULL_NODE
