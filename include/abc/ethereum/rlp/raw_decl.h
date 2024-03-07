// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_RAW_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_RAW_DECL

#pragma once

#include "object_type.h"

#include <abc/bytes_view.h>
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
read_kind(bytes_view_t buf) -> expected<decoded_type_and_size, std::error_code>;

auto
split(bytes_view_t buf) -> expected<decoded_item, std::error_code>;

auto
split_bytes(bytes_view_t buf) -> expected<decoded_item, std::error_code>;

//template <std::unsigned_integral T>
//split_integer(bytes_view_t buf) -> expected<decoded_item, std::error_code>;

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_RAW_DECL
