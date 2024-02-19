// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_RLP_ETH1_HEADER_FWD_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_RLP_ETH1_HEADER_FWD_DECL

#pragma once

#include <abc/ethereum/types/eth1/header_fwd_decl.h>

#include <abc/ethereum/rlp/adaptor/adaptor_base_fwd_decl.h>
#include <abc/ethereum/rlp/adaptor/as_fwd_decl.h>

namespace abc::ethereum::rlp::adaptor
{

template <>
struct as<types::eth1::header>;

template <>
struct convert<types::eth1::header>;

template <>
struct pack<types::eth1::header>;

template <>
struct object<types::eth1::header>;

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_RLP_ETH1_HEADER_FWD_DECL
