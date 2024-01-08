// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ABC_BYTES
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ABC_BYTES

#pragma once

#include "abc/ethereum/rlp/concepts.h"
#include "abc/ethereum/rlp/error.h"
#include "abc/ethereum/rlp/pack.h"

#include <abc/bytes.h>
#include <abc/error.h>

namespace abc::ethereum::rlp::adaptor
{

template <abc::byte_numbering ByteNumbering>
struct convert<abc::bytes<ByteNumbering>>
{
    auto
    operator()(rlp::object const & o, abc::bytes<ByteNumbering> & v) const -> rlp::object const &
    {
        if (o.type != rlp::type::bytes)
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::type_error));
        }

        v = abc::bytes<ByteNumbering>::template from<byte_numbering::none>(std::span{ o.data.bytes.ptr, o.data.bytes.size });
        return o;
    }
};

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
