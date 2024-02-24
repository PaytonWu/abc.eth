// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_RLP_ADDRESS)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_RLP_ADDRESS

#pragma once

#include "address_decl.h"

#include <abc/ethereum/rlp/adaptor/adaptor_base.h>
#include <abc/ethereum/rlp/pack.h>

namespace abc::ethereum::rlp::adaptor
{

template <packing_stream Stream>
auto
pack<types::address>::operator()(packer<Stream> & o, types::address const & v) const -> packer<Stream> &
{
    o.pack(v.bytes());
    return o;
}

} // namespace abc::ethereum::rlp::adaptor

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_RLP_ADDRESS
