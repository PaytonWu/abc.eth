// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NODE_FLAG
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NODE_FLAG

#pragma once

#include "node_flag_decl.h"

namespace abc::ethereum::trie
{

constexpr node_flag::node_flag(trie::hash_node const & hash_node, bool dirty) : hash_node_{hash_node}, dirty_{dirty}
{
}

constexpr node_flag::node_flag(trie::hash_node const & hash_node) : hash_node_{hash_node}
{
}

constexpr node_flag::node_flag(bool dirty) : dirty_{dirty}
{
}

constexpr auto
node_flag::hash_node() const noexcept -> trie::hash_node const &
{
    return hash_node_;
}

constexpr auto
node_flag::dirty() const noexcept -> bool
{
    return dirty_;
}

constexpr auto
node_flag::hash_node(trie::hash_node const & value) -> void
{
    hash_node_ = value;
}

constexpr auto
node_flag::dirty(bool value) -> void
{
    dirty_ = value;
}

} // namespace abc::ethereum::trie

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NODE_FLAG
