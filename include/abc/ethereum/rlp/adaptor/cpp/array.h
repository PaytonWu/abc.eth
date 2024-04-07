// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_CPP_ARRAY)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_CPP_ARRAY

#pragma once

#include <abc/ethereum/rlp/adaptor/adaptor_base.h>
#include <abc/ethereum/rlp/concepts.h>
#include <abc/ethereum/rlp/object.h>
#include <abc/ethereum/rlp/pack.h>

#include <array>
#include <utility>

namespace abc::ethereum::rlp::adaptor
{

namespace details::array
{

template <typename T, std::size_t N1, std::size_t... I1, std::size_t N2, std::size_t... I2>
constexpr std::array<T, N1 + N2>
concat(std::array<T, N1> && a1, std::array<T, N2> && a2, std::index_sequence<I1...>, std::index_sequence<I2...>)
{
    return {{std::move(a1[I1])..., std::move(a2[I2])...}};
}

template <typename T, std::size_t N1, std::size_t N2>
constexpr std::array<T, N1 + N2>
concat(std::array<T, N1> && a1, std::array<T, N2> && a2)
{
    return concat(std::move(a1), std::move(a2), std::make_index_sequence<N1>{}, std::make_index_sequence<N2>{});
}

template <typename T, std::size_t N>
struct as_impl
{
    static std::array<T, N>
    as(rlp::object const & o)
    {
        rlp::object * p = &o.data.array.ptr[N - 1];
        return concat(as_impl<T, N - 1>::as(o), std::array<T, 1>{{p->as<T>()}});
    }
};

template <typename T>
struct as_impl<T, 1>
{
    static std::array<T, 1>
    as(rlp::object const & o)
    {
        rlp::object * p = o.data.array.ptr;
        return std::array<T, 1>{{p->as<T>()}};
    }
};

template <typename T>
struct as_impl<T, 0>
{
    static std::array<T, 0>
    as(rlp::object const &)
    {
        return std::array<T, 0>{};
    }
};

} // namespace details::array

template <typename T, std::size_t N>
struct as<std::array<T, N>>
{
    auto
    operator()(rlp::object const & o) const -> std::array<T, N>
    {
        if (o.type != rlp::type::list)
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::type_error));
        }

        if (o.data.array.size > N)
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::type_error));
        }

        return details::array::as_impl<T, N>::as(o);
    }
};

template <typename T, std::size_t N>
struct convert<std::array<T, N>>
{
    auto
    operator()(rlp::object const & o, std::array<T, N> & v) const -> rlp::object const &
    {
        if (o.type != rlp::type::list)
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::type_error));
        }
        if (o.data.array.size > N)
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::type_error));
        }
        if (o.data.array.size > 0)
        {
            rlp::object * p = o.data.array.ptr;
            rlp::object * const pend = o.data.array.ptr + o.data.array.size;
            T * it = &v[0];
            do
            {
                p->convert(*it);
                ++p;
                ++it;
            } while (p < pend);
        }
        return o;
    }
};

template <typename T, std::size_t N>
struct pack<std::array<T, N>>
{
    template <typename Stream>
    auto
    operator()(packer<Stream> & o, std::array<T, N> const & v) const -> packer<Stream> &
    {
        for (auto const & e : v)
        {
            o.pack(e);
        }

        return o;
    }
};

} // namespace abc::ethereum::rlp::adaptor

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_CPP_ARRAY
