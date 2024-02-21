// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_CPP_SHARED_PTR)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_CPP_SHARED_PTR

#pragma once

#include <abc/ethereum/rlp/adaptor/adaptor_base.h>
#include <abc/ethereum/rlp/concepts.h>
#include <abc/ethereum/rlp/pack.h>
#include <abc/ethereum/rlp/object.h>

#include <memory>

namespace abc::ethereum::rlp::adaptor
{

template <typename T>
struct as<std::shared_ptr<T>> {
    auto
    operator()(rlp::object const & o) const -> std::shared_ptr<T>
    {
        if (o.is_nil())
        {
            return nullptr;
        }

        return std::make_shared<T>(o.as<T>());
    }
};

template <typename T>
struct convert<std::shared_ptr<T>>
{
    auto
    operator()(rlp::object const & o, std::shared_ptr<T> & v) const -> rlp::object const &
    {
        if (o.is_nil())
        {
            v.reset();
        }
        else
        {
            v = std::make_shared<T>();
            adaptor::convert<T>{}(o, *v);
        }
        return o;
    }
};

template <typename T>
struct pack<std::shared_ptr<T>>
{
    template <typename Stream>
    auto
    operator()(packer<Stream>& o, std::shared_ptr<T> const & v) const -> packer<Stream> &
    {
        if (v != nullptr)
        {
            o.pack(*v);
        }

        return o;
    }
};

}


#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_CPP_SHARED_PTR
