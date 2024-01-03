// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ADAPTOR_BASE_FWD_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ADAPTOR_BASE_FWD_DECL

#pragma once

namespace abc::ethereum::rlp::adaptor
{

template <typename T, typename Enabler = void>
struct convert;

template <typename T, typename Enabler = void>
struct pack;

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ADAPTOR_BASE_FWD_DECL
