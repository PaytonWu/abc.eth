// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_RLP_FULL_NODE)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_RLP_FULL_NODE

#pragma once

#include "full_node_decl.h"

#include <abc/ethereum/rlp/adaptor/adaptor_base.h>
#include <abc/ethereum/rlp/pack.h>
#include <abc/ethereum/rlp/type_traits.h>
#include <abc/ethereum/trie/hash_node_decl.h>
#include <abc/ethereum/trie/short_node_decl.h>
#include <abc/utility.h>

#include <cassert>

namespace abc::ethereum::rlp::adaptor
{

template <packing_stream Stream>
auto
pack<trie::full_node>::operator()(packer<Stream> & o, trie::full_node const & v) const -> packer<Stream> &
{
    for (auto i = 0uz; i < trie::full_node::children_size; ++i)
    {
        auto child_ptr = v.child(i);
        if (child_ptr != nullptr)
        {
            switch (child_ptr->type())
            {
                case trie::node_type::full_node:
                {
                    o.pack(*static_cast<trie::full_node const *>(child_ptr.get()));
                    break;
                }
                case trie::node_type::short_node:
                {
                    o.pack(*static_cast<trie::short_node const *>(child_ptr.get()));
                    break;
                }
                case trie::node_type::hash_node:
                {
                    o.pack(*static_cast<trie::hash_node const *>(child_ptr.get()));
                    break;
                }
                default:
                {
                    assert(false);
                    break;
                }
            }
        }
        else
        {
            o.pack_empty_bytes();
        }
    }

    return o;
}

} // namespace abc::ethereum::rlp::adaptor

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_RLP_FULL_NODE
