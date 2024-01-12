// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ADDRESS
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ADDRESS

#pragma once

#include "adaptor_base.h"
#include "as_fwd_decl.h"

#include "abc/ethereum/types/address.h"
#include "abc/ethereum/rlp/concepts.h"
#include "abc/ethereum/rlp/pack.h"

namespace abc::ethereum::rlp::adaptor
{

template <>
struct as<types::address>
{
    auto
    operator()(rlp::object const & o) const -> types::address
    {
        if (o.type != rlp::type::bytes)
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::type_error));
        }

        auto r = types::address::from(bytes_be_view_t::from(bytes_view_t{ o.data.bytes.ptr, o.data.bytes.size }));
        if (!r.has_value())
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::unpack_error));
        }
        return r.value();
    }
};

template <>
struct convert<types::address>
{
    auto
    operator()(rlp::object const & o, types::address & v) const -> rlp::object const &
    {
        if (o.type != rlp::type::bytes)
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::type_error));
        }

        auto r = types::address::from(bytes_be_view_t::from(bytes_view_t{ o.data.bytes.ptr, o.data.bytes.size }));
        if (!r.has_value())
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::unpack_error));
        }
        v = r.value();

        return o;
    }
};

template <>
struct pack<types::address> {
    template <packing_stream Stream>
    auto
    operator()(packer<Stream> & o, types::address const & v) const -> packer<Stream> &
    {
        o.pack_address(v);
        return o;
    }
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ADDRESS
