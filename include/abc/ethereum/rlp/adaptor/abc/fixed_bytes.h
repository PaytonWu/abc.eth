// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ABC_FIXED_BYTES
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ABC_FIXED_BYTES

#pragma once

#include "abc/ethereum/rlp/concepts.h"
#include "abc/ethereum/rlp/pack.h"
#include <abc/fixed_bytes.h>

namespace abc::ethereum::rlp::adaptor
{

template <std::size_t N, byte_numbering ByteNumbering>
struct as<abc::fixed_bytes<N, ByteNumbering>>
{
    auto
    operator()(rlp::object const & o) const -> abc::fixed_bytes<N, ByteNumbering>
    {
        if (o.type != rlp::type::bytes)
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::type_error));
        }

        auto r = abc::fixed_bytes<N, ByteNumbering>::template from<byte_numbering::none>(bytes_view_t{ o.data.bytes.ptr, o.data.bytes.size });
        if (r.has_value())
        {
            return r.value();
        }

        abc::throw_error(r.error());
    }
};

template <std::size_t N, byte_numbering ByteNumbering>
struct convert<abc::fixed_bytes<N, ByteNumbering>>
{
    auto
    operator()(rlp::object const & o, abc::fixed_bytes<N, ByteNumbering> & v) const -> rlp::object const &
    {
        if (o.type != rlp::type::bytes)
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::type_error));
        }

        auto r = abc::fixed_bytes<N, ByteNumbering>::template from<byte_numbering::none>(bytes_view_t{ o.data.bytes.ptr, o.data.bytes.size });
        if (r.has_value())
        {
            v = r.value();
        }
        else
        {
            abc::throw_error(r.error());
        }

        return o;
    }
};

template <std::size_t N, byte_numbering ByteNumbering>
struct pack<abc::fixed_bytes<N, ByteNumbering>>
{
    template <packing_stream Stream>
    auto
    operator()(packer<Stream> & o, abc::fixed_bytes<N, ByteNumbering> const & v) const -> packer<Stream> &
    {
        o.pack_fixed_bytes(v);
        return o;
    }
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ABC_FIXED_BYTES
