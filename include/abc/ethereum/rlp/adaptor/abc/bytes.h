// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ABC_BYTES
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ABC_BYTES

#pragma once

#include "abc/ethereum/rlp/concepts.h"
#include "abc/ethereum/rlp/pack.h"
#include <abc/bytes.h>

namespace abc::ethereum::rlp::adaptor
{

template <abc::byte_numbering ByteNumbering>
struct pack<abc::bytes<ByteNumbering>>
{
    template <packing_stream Stream>
    auto
    operator()(packer<Stream> & o, abc::bytes<ByteNumbering> const & v) const -> packer<Stream> &
    {
        o.pack_bytes(v);
        return o;
    }
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ABC_BYTES
