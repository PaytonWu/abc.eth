// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_SHORT_NODE)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_SHORT_NODE

#pragma once

#include "short_node_decl.h"

namespace abc::ethereum::trie
{

constexpr auto
short_node::type() const noexcept -> node_type
{
    return node_type::short_node;
}

constexpr auto
short_node::value() const noexcept -> std::shared_ptr<node_face> const &
{
    return value_;
}

} // namespace abc::ethereum::trie

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_SHORT_NODE
