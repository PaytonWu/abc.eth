// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_SERDE_FWD_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_SERDE_FWD_DECL

#pragma once

#include "concepts.h"
#include "pack_fwd_decl.h"

#include <type_traits>

namespace abc::ethereum::rlp
{

template <packing_stream Stream, typename T> requires (!std::is_array_v<T>)
auto
serialize_to(packer<Stream> & packer, T const & value) -> rlp::packer<Stream> &;

template <packing_stream Stream, typename T, std::size_t N>
auto
serialize_to(packer<Stream> & packer, T const (&v)[N]) -> rlp::packer<Stream> &;

} // namespace abc::ethereum::rlp

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_SERDE_FWD_DECL
