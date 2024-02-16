// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_UNSIGNED_INTEGRAL
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_UNSIGNED_INTEGRAL

#pragma once

#include "adaptor_base.h"
#include "as_fwd_decl.h"

#include <abc/ethereum/rlp/concepts.h>
#include <abc/ethereum/rlp/pack.h>

#include <concepts>

namespace abc::ethereum::rlp::adaptor
{

template <std::unsigned_integral T>
struct as<T>
{
    auto
    operator()(rlp::object const & o) const -> T
    {
        if (o.type != rlp::type::bytes)
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::type_error));
        }

        if (o.data.bytes.size > sizeof(T))
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::unpack_error));
        }

        return bytes_be_view_t::from(bytes_view_t{ o.data.bytes.ptr, o.data.bytes.size }).template to<T>();
    }
};

template <std::unsigned_integral T>
struct convert<T>
{
    auto
    operator()(rlp::object const & o, T & v) const -> rlp::object const &
    {
        if (o.type != rlp::type::bytes)
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::type_error));
        }

        if (o.data.bytes.size > sizeof(T))
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::unpack_error));
        }

        v = bytes_be_view_t::from(bytes_view_t{ o.data.bytes.ptr, o.data.bytes.size }).template to<T>();

        return o;
    }
};

template <std::unsigned_integral T>
struct pack<T>
{
    template <packing_stream Stream>
    auto
    operator()(packer<Stream> & o, T const & v) const -> packer<Stream> &
    {
        o.pack_unsigned_integral(v);
        return o;
    }
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_UNSIGNED_INTEGRAL
