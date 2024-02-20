// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_RLP_ADDRESS_FWD_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_RLP_ADDRESS_FWD_DECL

#pragma once

#include <abc/ethereum/types/address_fwd_decl.h>
#include <abc/ethereum/rlp/adaptor/adaptor_base_decl.h>

namespace abc::ethereum::rlp::adaptor
{

template <>
struct as<types::address>;

template <>
struct convert<types::address>;

template <>
struct pack<types::address>;

} // namespace abc::ethereum::rlp::adaptor

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_RLP_ADDRESS_FWD_DECL
