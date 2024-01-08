// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ADDRESS
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ADDRESS

#pragma once

#include "abc/ethereum/types/address.h"
#include "abc/ethereum/rlp/concepts.h"
#include "abc/ethereum/rlp/pack.h"

namespace abc::ethereum::rlp::adaptor
{

template <>
struct pack<types::address> {
    template <packing_stream Stream>
    auto
    operator()(packer<Stream> & o, types::address const & v) const -> packer<Stream> &
    {
        o.pack_address(v);
        return o;
    }
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ADDRESS
