// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ABC_UINT128
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ABC_UINT128

#pragma once

#include "abc/ethereum/rlp/concepts.h"
#include "abc/ethereum/rlp/pack.h"
#include <abc/uint128.h>

namespace abc::ethereum::rlp::adaptor
{

template <>
struct pack<abc::uint128_t>
{
    template <packing_stream Stream>
    auto
    operator()(packer<Stream> & o, uint128_t const & v) const -> packer<Stream> &
    {
        o.pack_uint128(v);
        return o;
    }
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ABC_UINT128
