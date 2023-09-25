// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_UNPACK_DECL
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_UNPACK_DECL

#pragma once

#include <cstddef>

namespace abc::ethereum::rlp {

using unpack_reference_func = auto (*)(void const * ptr, std::size_t size) -> bool;

inline constexpr std::size_t RLP_UNPACKER_INIT_BUFFER_SIZE{64*1024};
inline constexpr std::size_t RLP_UNPACKER_RESERVE_SIZE{32*1024};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_UNPACK_DECL
