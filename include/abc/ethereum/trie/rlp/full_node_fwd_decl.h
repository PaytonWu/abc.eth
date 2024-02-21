// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_RLP_FULL_NODE_FWD_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_RLP_FULL_NODE_FWD_DECL

#pragma once

#include <abc/ethereum/trie/full_node_fwd_decl.h>
#include <abc/ethereum/rlp/adaptor/adaptor_base_decl.h>

namespace abc::ethereum::rlp::adaptor
{

template <>
struct as<trie::full_node>;

template <>
struct convert<trie::full_node>;

template <>
struct pack<trie::full_node>;

} // namespace abc::ethereum::rlp::adaptor

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_RLP_FULL_NODE_FWD_DECL
