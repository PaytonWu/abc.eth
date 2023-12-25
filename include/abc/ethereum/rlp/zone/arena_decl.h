// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ZONE_ARENA_DECL
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ZONE_ARENA_DECL

#pragma once

#include "arena_fwd_decl.h"

#include <cstdint>

namespace abc::ethereum::rlp::zone {

inline constexpr std::size_t ABC_RLP_ARENA_CHUNK_SIZE = { 8192 };
inline constexpr std::size_t ABC_RLP_ARENA_ALIGNMENT = { sizeof(void*) };

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ZONE_ARENA_DECL
