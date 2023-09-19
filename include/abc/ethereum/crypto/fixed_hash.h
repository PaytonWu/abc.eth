// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_CRYPTO_FIXED_HASH
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_CRYPTO_FIXED_HASH

#pragma once

#include <abc/fixed_bytes.h>

namespace abc::ethereum::crypto {

using h256_t = abc::fixed_bytes<32, abc::byte_numbering::msb0>;

}


#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_CRYPTO_FIXED_HASH
