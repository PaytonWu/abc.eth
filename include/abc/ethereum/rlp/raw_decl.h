// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_RAW_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_RAW_DECL

#pragma once

#include "object_type.h"

#include <abc/bytes.h>
#include <abc/expected.h>

#include <cstdint>
#include <string_view>
#include <system_error>

namespace abc::ethereum::rlp
{

struct decoded_item
{
    type type{type::invalid};
    bytes_view_t content{};
    bytes_view_t rest{};
};

template <std::unsigned_integral T>
struct decoded_unsigned_integral_item
{
    T value{0};
    bytes_view_t rest{};
};

struct decoded_type_and_size
{
    type type{type::invalid};
    std::uint64_t tag_size{0};
    std::uint64_t content_size{0};
};

[[nodiscard]] constexpr auto
bytes_size(bytes_view_t bytes) noexcept -> std::uint64_t;

[[nodiscard]] constexpr auto
string_size(std::string_view str) noexcept -> std::uint64_t;

[[nodiscard]] constexpr auto
list_size(std::uint64_t content_size) noexcept -> std::uint64_t;

[[nodiscard]] auto
read_size(bytes_view_t buf, byte size_of_length) -> expected<std::uint64_t, std::error_code>;

[[nodiscard]] auto
read_kind(bytes_view_t buf) -> expected<decoded_type_and_size, std::error_code>;

auto
split(bytes_view_t buf) -> expected<decoded_item, std::error_code>;

auto
split_bytes(bytes_view_t buf) -> expected<decoded_item, std::error_code>;

template <std::unsigned_integral T>
auto
split_unsigned_integral(bytes_view_t buf) -> expected<decoded_unsigned_integral_item<T>, std::error_code>;

auto
split_list(bytes_view_t buf) -> expected<decoded_item, std::error_code>;

auto
count_value(bytes_view_t buf) -> expected<std::uint64_t, std::error_code>;

auto
append_unsigned_integral(abc::bytes_t & buffer, std::uint64_t value) -> void;

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_RAW_DECL
