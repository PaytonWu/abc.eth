// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_RLP_FULL_NODE_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_RLP_FULL_NODE_DECL

#pragma once

#include "full_node_fwd_decl.h"

#include <abc/ethereum/trie/full_node_decl.h>

namespace abc::ethereum::rlp::adaptor
{

template <>
struct as<trie::full_node>
{
    auto
    operator()(rlp::object const & o) const -> trie::full_node;
};

template <>
struct convert<trie::full_node>
{
    auto
    operator()(rlp::object const & o, trie::full_node & v) const -> rlp::object const &;
};

template <>
struct pack<trie::full_node>
{
    template <packing_stream Stream>
    auto
    operator()(packer<Stream> & o, trie::full_node const & v) const -> packer<Stream> &;
};

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_RLP_FULL_NODE_DECL
