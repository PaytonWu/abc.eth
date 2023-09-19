// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_BYTES
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_BYTES

#pragma once

#include <abc/fixed_bytes.h>

namespace abc::ethereum::types {

using bytes32_t = fixed_bytes<32, byte_numbering::none>;

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_BYTES
