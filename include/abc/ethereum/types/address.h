// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_ADDRESS
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_ADDRESS

#pragma once

#include "address_decl.h"

namespace abc::ethereum::types
{

constexpr auto
address::bytes() const noexcept -> value_type const &
{
    return raw_address_;
}

constexpr auto
address::hex_string() const -> abc::hex_string
{
    return abc::hex_string::from<byte_numbering::msb0>(raw_address_);
}

constexpr auto
address::zero() -> address const &
{
    static constexpr address zero_address{};
    return zero_address;
}

} // namespace abc::ethereum::types

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_ADDRESS
