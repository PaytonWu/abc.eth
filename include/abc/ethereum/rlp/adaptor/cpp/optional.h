// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_CPP_OPTIONAL
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_CPP_OPTIONAL

#pragma once

#include "abc/ethereum/rlp/adaptor/adaptor_base.h"
#include "abc/ethereum/rlp/concepts.h"
#include "abc/ethereum/rlp/pack.h"
#include "abc/ethereum/rlp/object.h"

#include <optional>

namespace abc::ethereum::rlp::adaptor
{

template <typename T>
struct as<std::optional<T>> {
    auto
    operator()(rlp::object const & o) const -> std::optional<T>
    {
        if (o.is_nil())
        {
            return std::nullopt;
        }

        return o.as<T>();
    }
};

template <typename T>
struct convert<std::optional<T>>
{
    auto
    operator()(rlp::object const & o, std::optional<T> & v) const -> rlp::object const &
    {
        if (o.is_nil())
        {
            v = std::nullopt;
        }
        else
        {
            T t;
            adaptor::convert<T>{}(o, t);
            v = t;
        }
        return o;
    }
};

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
