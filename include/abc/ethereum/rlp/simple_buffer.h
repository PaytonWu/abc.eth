// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_SIMPLE_BUFFER)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_SIMPLE_BUFFER

#pragma once

#include "simple_buffer_decl.h"

namespace abc::ethereum::rlp
{

template <byte_numbering ByteNumbering>
auto
simple_buffer::bytes_view() const noexcept -> abc::bytes_view<ByteNumbering>
{
    return abc::bytes_view<ByteNumbering>{bytes_view_t{buffer_}};
}

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_SIMPLE_BUFFER
