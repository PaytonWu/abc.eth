// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ABC_UINT128
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ABC_UINT128

#pragma once

#include "abc/ethereum/rlp/adaptor/adaptor_base.h"
#include "abc/ethereum/rlp/adaptor/as_fwd_decl.h"
#include "abc/ethereum/rlp/concepts.h"
#include "abc/ethereum/rlp/pack.h"

#include <abc/uint128.h>

namespace abc::ethereum::rlp::adaptor
{

template <>
struct as<uint128_t>
{
    auto
    operator()(rlp::object const & o) const -> uint128_t
    {
        if (o.type != rlp::type::bytes)
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::type_error));
        }

        auto r = uint128_t::from(bytes_be_view_t::from(bytes_view_t{ o.data.bytes.ptr, o.data.bytes.size }));
        if (r.has_value())
        {
            return r.value();
        }

        abc::throw_error(make_error_code(abc::ethereum::rlp::errc::unpack_error));
    }
};

template <>
struct convert<uint128_t>
{
    auto
    operator()(rlp::object const & o, uint128_t & v) const -> rlp::object const &
    {
        if (o.type != rlp::type::bytes)
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::type_error));
        }

        auto r = uint128_t::from(bytes_be_view_t::from(bytes_view_t{ o.data.bytes.ptr, o.data.bytes.size }));
        if (r.has_value())
        {
            v = r.value();
        }
        else
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::unpack_error));
        }

        return o;
    }
};

template <>
struct pack<abc::uint128_t>
{
    template <packing_stream Stream>
    auto
    operator()(packer<Stream> & o, uint128_t const & v) const -> packer<Stream> &
    {
        o.pack_uint128(v);
        return o;
    }
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ABC_UINT128
