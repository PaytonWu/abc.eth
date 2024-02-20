// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_RLP_ETH1_HEADER_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_RLP_ETH1_HEADER_DECL

#pragma once

#include "header_fwd_decl.h"

#include <abc/ethereum/types/eth1/header_decl.h>
#include <abc/ethereum/rlp/adaptor/adaptor_base.h>

namespace abc::ethereum::rlp::adaptor
{

template <>
struct as<types::eth1::header>
{
    auto
    operator()(rlp::object const & o) const -> types::eth1::header;
};

template <>
struct convert<types::eth1::header>
{
    auto
    operator()(rlp::object const & o, types::eth1::header & v) const -> rlp::object const &;
};

template <>
struct pack<types::eth1::header> {
    template <packing_stream Stream>
    auto
    operator()(packer<Stream> & o, types::eth1::header const & v) const -> packer<Stream> &;
};

template <>
struct object<types::eth1::header>
{
    auto
    operator()(rlp::object& , types::eth1::header const & ) const -> void;
};

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_RLP_ETH1_HEADER_DECL
