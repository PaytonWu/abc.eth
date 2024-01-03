// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ADAPTOR_BASE)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ADAPTOR_BASE

#pragma once

#include "adaptor_base_decl.h"
#include "../pack_fwd_decl.h"

namespace abc::ethereum::rlp
{

template <typename T>
requires (!std::is_array_v<T> && !std::is_pointer_v<T>)
auto
operator>> (msgpack::object const& o, T& v) -> object const &
{
    return adaptor::convert<T>{}(o, v);
}

template <typename T, std::size_t N>
auto
operator>> (object const& o, T(&v)[N]) -> object const &
{
    return adaptor::convert<T[N]>()(o, v);
}

template <typename Stream, typename T>
requires (!std::is_array_v<T>)
auto
operator<< (msgpack::packer<Stream>& o, T const& v) -> packer<Stream> &
{
    return adaptor::pack<T>{}(o, v);
}

template <is_packing_stream Stream, typename T, std::size_t N>
auto
operator<< (msgpack::packer<Stream>& o, const T(&v)[N]) -> packer<Stream> &
{
    return adaptor::pack<T[N]>{}(o, v);
}

template <typename T>
requires (!std::is_array_v<T>)
auto
operator<< (msgpack::object& o, T const& v) -> void
{
    adaptor::object<T>{}(o, v);
}

template <typename T, std::size_t N>
auto
operator<< (object & o, const T(&v)[N]) -> void
{
    adaptor::object<T[N]>{}(o, v);
}

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ADAPTOR_BASE
