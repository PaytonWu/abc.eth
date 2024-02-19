// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_TYPE_TRAITS)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_TYPE_TRAITS

#pragma once

#include <concepts>
#include <optional>
#include <type_traits>

namespace abc::ethereum::rlp
{

template <typename T>
struct is_list : std::false_type
{
};

template <typename T>
struct is_list<std::optional<T>> : is_list<T>
{
};

template <typename T>
inline constexpr bool is_list_v = is_list<T>::value;

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_TYPE_TRAITS
