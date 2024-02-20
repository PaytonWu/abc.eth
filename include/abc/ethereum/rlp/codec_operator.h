// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_CODEC_OPERATOR
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_CODEC_OPERATOR

#pragma once

#include "codec_operator_decl.h"
#include "adaptor/adaptor_base.h"

namespace abc::ethereum::rlp
{

template <typename T>
requires (!std::is_array_v<T> && !std::is_pointer_v<T>)
auto
operator>>(object const & o, T& v) -> object const &
{
    return adaptor::convert<T>{}(o, v);
}

template <typename T, std::size_t N>
auto
operator>>(object const & o, T(&v)[N]) -> object const &
{
    return adaptor::convert<T[N]>{}(o, v);
}

template <typename T>
requires (!std::is_array_v<T>)
auto
operator<<(object & o, T const& v) -> void
{
    adaptor::object<T>{}(o, v);
}

template <typename T, std::size_t N>
auto
operator<<(object & o, const T(&v)[N]) -> void
{
    adaptor::object<T[N]>{}(o, v);
}

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_CODEC_OPERATOR
