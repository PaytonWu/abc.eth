// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_CODEC_OPERATOR_DECL
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_CODEC_OPERATOR_DECL

#pragma once

#include "object_fwd_decl.h"

#include <type_traits>

namespace abc::ethereum::rlp
{

template <typename T>
requires (!std::is_array_v<T> && !std::is_pointer_v<T>)
auto
operator>> (object const& o, T& v) -> object const &;

template <typename T, std::size_t N>
auto
operator>> (object const& o, T(&v)[N]) -> object const &;

template <typename T>
requires (!std::is_array_v<T> && !std::is_pointer_v<T>)
auto
operator<< (object & o, T const& v) -> void;

template <typename T, std::size_t N>
auto
operator<< (object & o, const T(&v)[N]) -> void;

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_CODEC_OPERATOR_DECL
