// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_RAW_FWD_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_RAW_FWD_DECL

#pragma once

#include <concepts>

namespace abc::ethereum::rlp
{

struct [[nodiscard]] decoded_item;
struct [[nodiscard]] decoded_type_and_size;

template <std::unsigned_integral T>
struct [[nodiscard]] decoded_unsigned_integral_item;

} // namespace abc::ethereum::rlp

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_RAW_FWD_DECL
