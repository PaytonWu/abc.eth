// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_CONSTANTS_HASHES)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_CONSTANTS_HASHES

#pragma once

#include <abc/bytes_view.h>
#include <abc/fixed_hash.h>
#include <abc/hex_string.h>

namespace abc::ethereum::constants
{

constexpr h256_t empty_root_hash{h256_t::from(bytes_be_view_t{"0x56e81f171bcc55a6ff8345e692c0f86e5b48e01b996cadc001622fb5e363b421"}).value()};

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_CONSTANTS_HASHES
