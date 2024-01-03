// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ADAPTOR_BASE_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ADAPTOR_BASE_DECL

#pragma once

#include "../object_fwd_decl.h"
#include "../pack_fwd_decl.h"
#include "adaptor_base_fwd_decl.h"

#include <cstddef>
#include <type_traits>

namespace abc::ethereum::rlp::adaptor
{

template <typename T, typename Enabler>
struct convert {
    auto
    operator()(rlp::object const& o, T& v) const -> rlp::object const &;
};

template <typename T, typename Enabler>
struct pack {
    template <is_packing_stream Stream>
    auto
    operator()(packer<Stream>& o, T const& v) const -> packer<Stream> &;
};

template <typename T, typename Enabler>
struct object
{
    auto
    operator()(rlp::object& o, T const & v) const -> void;
};

}




#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ADAPTOR_BASE_DECL
