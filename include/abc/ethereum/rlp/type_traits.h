// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_TYPE_TRAITS)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_TYPE_TRAITS

#pragma once

#include <abc/uint128.h>
#include <abc/bytes_fwd_decl.h>
#include <abc/bytes_view_fwd_decl.h>
#include <abc/byte_bit_numbering.h>

#include <concepts>
#include <optional>
#include <string>
#include <string_view>
#include <type_traits>

namespace abc::ethereum::rlp
{

template <typename T>
struct is_list : std::true_type
{
};

template <>
struct is_list<char> : std::false_type
{
};

template <>
struct is_list<unsigned char> : std::false_type
{
};

template <>
struct is_list<signed char> : std::false_type
{
};

template <>
struct is_list<short> : std::false_type
{
};

template <>
struct is_list<unsigned short> : std::false_type
{
};

template <>
struct is_list<int> : std::false_type
{
};

template <>
struct is_list<unsigned int> : std::false_type
{
};

template <>
struct is_list<long> : std::false_type
{
};

template <>
struct is_list<unsigned long> : std::false_type
{
};

template <>
struct is_list<long long> : std::false_type
{
};

template <>
struct is_list<unsigned long long> : std::false_type
{
};

template <typename T>
struct is_list<std::optional<T>> : is_list<T>
{
};

template <>
struct is_list<std::string> : std::false_type
{
};

template <>
struct is_list<std::string_view> : std::false_type
{
};

template <byte_numbering ByteNumbering>
struct is_list<bytes<ByteNumbering>> : std::false_type
{
};

template <byte_numbering ByteNumbering>
struct is_list<bytes_view<ByteNumbering>> : std::false_type
{
};

template <std::size_t N, byte_numbering ByteNumbering>
struct is_list<fixed_bytes<N, ByteNumbering>> : std::false_type
{
};

template <>
struct is_list<uint128_t> : std::false_type
{
};

template <typename T>
inline constexpr bool is_list_v = is_list<T>::value;

} // namespace abc::ethereum::rlp

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_TYPE_TRAITS
