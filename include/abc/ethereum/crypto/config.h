// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_CRYPTO_CONFIG
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_CRYPTO_CONFIG

#pragma once

#include <abc/fixed_bytes.h>

namespace abc::ethereum::crypto {

using bytes65_be_t = fixed_bytes<65, byte_numbering::msb0>;
using bytes33_be_t = fixed_bytes<33, byte_numbering::msb0>;

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_CRYPTO_CONFIG
