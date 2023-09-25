// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_SYSDEP
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_SYSDEP

#pragma once

#include <bit>
#include <type_traits>
#include <concepts>

namespace abc::ethereum::rlp {

template <std::is_integral T>
inline auto load(std::byte * from) noexcept -> T {

}

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_SYSDEP
