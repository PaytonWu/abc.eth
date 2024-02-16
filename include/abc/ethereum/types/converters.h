// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_CONVERTERS
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_CONVERTERS

#pragma once

#include "address.h"

#include <abc/converter.h>

namespace abc
{

template <>
struct converter<ethereum::types::address::value_type, ethereum::types::address>
{
    static auto
    from(ethereum::types::address const & input)
    {
        return input.bytes();
    }
};

} // namespace abc

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_CONVERTERS
