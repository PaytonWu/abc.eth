// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_SERDE)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_SERDE

#pragma once

#include "serde_decl.h"

#include "adaptor/adaptor.h"

namespace abc::ethereum::rlp
{

template <packing_stream Stream, typename T> requires (!std::is_array_v<T>)
auto
serialize_to(packer<Stream> & packer, T const & v) -> rlp::packer<Stream> &
{
    return adaptor::pack<T>{}(packer, v);
}

template <packing_stream Stream, typename T, std::size_t N>
auto
serialize_to(packer<Stream> & packer, const T(&v)[N]) -> rlp::packer<Stream> &
{
    return adaptor::pack<T[N]>{}(packer, v);
}

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_SERDE
