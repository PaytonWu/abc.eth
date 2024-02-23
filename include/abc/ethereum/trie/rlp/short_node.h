// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_RLP_SHORT_NODE)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_RLP_SHORT_NODE

#pragma once

#include "short_node_decl.h"

#include <abc/ethereum/rlp/adaptor/adaptor_base.h>
#include <abc/ethereum/rlp/pack.h>
#include <abc/ethereum/rlp/type_traits.h>
#include <abc/utility.h>

#include <cassert>

namespace abc::ethereum::rlp::adaptor
{

template <packing_stream Stream>
auto
pack<trie::short_node>::operator()(packer<Stream> & o, trie::short_node const & v) const -> packer<Stream> &
{


    return o;
}

} // namespace abc::ethereum::rlp::adaptor

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_RLP_SHORT_NODE
