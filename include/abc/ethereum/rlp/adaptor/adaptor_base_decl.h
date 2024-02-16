// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ADAPTOR_BASE_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ADAPTOR_BASE_DECL

#pragma once

#include "adaptor_base_fwd_decl.h"

#include <abc/ethereum/rlp/object_fwd_decl.h>
#include <abc/ethereum/rlp/pack_fwd_decl.h>

#include <cstddef>
#include <type_traits>

namespace abc::ethereum::rlp::adaptor
{

template <typename T>
struct convert {
    auto
    operator()(rlp::object const & o, T & v) const -> rlp::object const &;
};

template <typename T>
struct pack {
    template <packing_stream Stream>
    auto
    operator()(packer<Stream>& o, T const& v) const -> packer<Stream> &;
};

template <typename T>
struct object
{
    auto
    operator()(rlp::object& o, T const & v) const -> void;
};

}




#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ADAPTOR_BASE_DECL
