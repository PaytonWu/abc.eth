// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NODE_FLAG_DECL
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NODE_FLAG_DECL

#pragma once

#include "node_flag_fwd_decl.h"

#include "hash_node_decl.h"

namespace abc::ethereum::trie
{

class node_flag
{
private:
    hash_node hash_node_{};
    bool dirty_{false};

public:
    node_flag() = default;

    constexpr node_flag(hash_node const & hash_node, bool dirty);
    constexpr explicit node_flag(hash_node const & hash_node);
    constexpr explicit node_flag(bool dirty);

    constexpr auto
    hash_node() const noexcept -> hash_node const &;

    constexpr auto
    dirty() const noexcept -> bool;

    constexpr auto
    hash_node(trie::hash_node const & value) -> void;

    constexpr auto
    dirty(bool value) -> void;
};

} // namespace abc::ethereum::trie

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NODE_FLAG_DECL
