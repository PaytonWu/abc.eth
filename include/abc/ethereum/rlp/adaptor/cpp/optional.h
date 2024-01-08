// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_CPP_OPTIONAL
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_CPP_OPTIONAL

#pragma once

#include "abc/ethereum/rlp/concepts.h"
#include "abc/ethereum/rlp/pack.h"

#include <optional>

namespace abc::ethereum::rlp::adaptor
{

template <typename T>
struct pack<std::optional<T>>
{
    template <typename Stream>
    auto
    operator()(packer<Stream>& o, std::optional<T> const & v) const -> packer<Stream> &
    {
        o.pack_optional(v);
        return o;
    }
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_CPP_OPTIONAL
