// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_RLP_ADDRESS_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_RLP_ADDRESS_DECL

#pragma once

#include "address_fwd_decl.h"

#include <abc/ethereum/types/address_decl.h>

namespace abc::ethereum::rlp::adaptor
{

template <>
struct as<types::address>
{
    auto
    operator()(rlp::object const & o) const -> types::address;
};

template <>
struct convert<types::address>
{
    auto
    operator()(rlp::object const & o, types::address & v) const -> rlp::object const &;
};

template <>
struct pack<types::address>
{
    template <packing_stream Stream>
    auto
    operator()(packer<Stream> & o, types::address const & v) const -> packer<Stream> &;
};

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_RLP_ADDRESS_DECL
