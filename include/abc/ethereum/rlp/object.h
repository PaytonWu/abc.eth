// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_OBJECT)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_OBJECT

#pragma once

#include "object_decl.h"
#include "adaptor/as.h"

#include <utility>

namespace abc::ethereum::rlp
{

template <typename T>
requires has_as<T>
auto
object::as() const -> T
{
    return adaptor::as<T>{}(*this);
}

template <typename T>
requires (!has_as<T>)
auto
object::as() const -> T
{
    T v;
    convert(v);
    return v;
}

template <typename T>
requires (!std::is_array_v<T> && !std::is_pointer_v<T>)
auto
object::convert(T & v) const -> void
{
    operator>>(*this, v);
}

template <typename T, std::size_t N>
auto
object::convert(T (& v)[N]) const -> void
{
    operator>>(*this, v);
}

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_OBJECT
