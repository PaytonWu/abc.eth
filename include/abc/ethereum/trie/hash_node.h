// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_HASH_NODE
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_HASH_NODE

#pragma once

#include "hash_node_decl.h"

namespace abc::ethereum::trie
{

constexpr auto
hash_node::type() const noexcept -> node_type
{
    return node_type::hash;
}

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_HASH_NODE
