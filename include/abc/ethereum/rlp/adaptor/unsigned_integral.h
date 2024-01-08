// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_UNSIGNED_INTEGRAL
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_UNSIGNED_INTEGRAL

#pragma once

#include "abc/ethereum/rlp/concepts.h"
#include "abc/ethereum/rlp/pack.h"

#include <concepts>

namespace abc::ethereum::rlp::adaptor
{

template <std::unsigned_integral T>
struct pack<T>
{
    template <packing_stream Stream>
    auto
    operator()(packer<Stream> & o, T const & v) const -> packer<Stream> &
    {
        o.pack_unsigned_integral(v);
        return o;
    }
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_UNSIGNED_INTEGRAL
