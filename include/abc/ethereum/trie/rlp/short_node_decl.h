// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_RLP_SHORT_NODE_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_RLP_SHORT_NODE_DECL

#pragma once

#include "short_node_fwd_decl.h"

#include <abc/ethereum/trie/short_node_decl.h>

namespace abc::ethereum::rlp::adaptor
{

template <>
struct as<trie::short_node>
{
    auto
    operator()(rlp::object const & o) const -> trie::short_node;
};

template <>
struct convert<trie::short_node>
{
    auto
    operator()(rlp::object const & o, trie::short_node & v) const -> rlp::object const &;
};

template <>
struct pack<trie::short_node>
{
    template <packing_stream Stream>
    auto
    operator()(packer<Stream> & o, trie::short_node const & v) const -> packer<Stream> &;
};

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_RLP_SHORT_NODE_DECL
