// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_RAW)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_RAW

#pragma once

#include "raw_decl.h"

#include "error.h"

namespace abc::ethereum::rlp
{

namespace
{

[[nodiscard]] constexpr auto
int_size(std::uint64_t i) -> int
{
    int size = 1;
    for (;; ++size)
    {
        if (i >>= 8; i == 0)
        {
            return size;
        }
    }
}

[[nodiscard]] constexpr auto
head_size(std::uint64_t size) -> int
{
    if (size < 56)
    {
        return 1;
    }
    return 1 + int_size(size);
}

} // namespace

constexpr auto
bytes_size(bytes_view_t bytes) noexcept -> std::uint64_t
{
    auto const sz = bytes.size();

    switch (sz)
    {
        case 0:
            return 1;
        case 1:
            if (bytes[0] <= 0x7f)
            {
                return 1;
            }
            return 2;

        default:
            return static_cast<uint64_t>(head_size(static_cast<std::uint64_t>(sz)) + sz);
    }
}

constexpr auto
string_size(std::string_view string) noexcept -> std::uint64_t
{
    auto const sz = string.size();

    switch (sz)
    {
        case 0:
            return 1;
        case 1:
            if (static_cast<byte>(string[0]) <= static_cast<byte>(0x7f))
            {
                return 1;
            }
            return 2;

        default:
            return static_cast<uint64_t>(head_size(static_cast<std::uint64_t>(sz)) + sz);
    }
}

constexpr auto
list_size(std::uint64_t content_size) noexcept -> std::uint64_t
{
    return static_cast<uint64_t>(head_size(content_size)) + content_size;
}

template <std::unsigned_integral T>
auto
split_unsigned_integral(bytes_view_t buf) -> expected<decoded_unsigned_integral_item<T>, std::error_code>
{
    return split_bytes(buf).transform([](decoded_item const & decoded_item) -> decoded_unsigned_integral_item<T> {
        if (decoded_item.content.empty())
        {
            return decoded_unsigned_integral_item<T>{.value = 0, .rest = decoded_item.rest};
        }

        if (decoded_item.content.size() == 1)
        {
            if (decoded_item.content[0] == 0)
            {
                return make_unexpected(make_error_code(errc::non_canonical_integral));
            }

            return decoded_unsigned_integral_item<T>{.value = static_cast<T>(decoded_item.content[0]), .rest = decoded_item.rest};
        }

        if (decoded_item.content.size() > 8)
        {
            return make_unexpected(make_error_code(errc::uint_overflow));
        }

        return read_size(decoded_item.content, static_cast<byte>(decoded_item.content.size()))
            .transform_error([](auto && error) { return make_error_code(errc::non_canonical_integral); })
            .transform([&decoded_item](std::uint64_t const size) { return decoded_unsigned_integral_item<T>{.value = size, .rest = decoded_item.rest}; });
    });
}

auto
append_unsigned_integral(abc::bytes_t & buffer, std::uint64_t value) -> void
{
    if (value == 0)
    {
        return buffer.push_back(0x80);
    }

    if (value < 128)
    {
        return buffer.push_back(static_cast<byte>(value));
    }

    if (value < (1ull << 8))
    {
        buffer.push_back(0x81);
        buffer.push_back(static_cast<byte>(value));
        return;
    }

    if (value < (1ull << 16))
    {
        buffer.push_back(0x82);
        buffer.push_back(static_cast<byte>(value >> 8));
        buffer.push_back(static_cast<byte>(value));
        return;
    }

    if (value < (1ull << 24))
    {
        buffer.push_back(0x83);
        buffer.push_back(static_cast<byte>(value >> 16));
        buffer.push_back(static_cast<byte>(value >> 8));
        buffer.push_back(static_cast<byte>(value));
        return;
    }

    if (value < (1ull << 32))
    {
        buffer.push_back(0x84);
        buffer.push_back(static_cast<byte>(value >> 24));
        buffer.push_back(static_cast<byte>(value >> 16));
        buffer.push_back(static_cast<byte>(value >> 8));
        buffer.push_back(static_cast<byte>(value));
        return;
    }

    if (value < (1ull << 40))
    {
        buffer.push_back(0x85);
        buffer.push_back(static_cast<byte>(value >> 32));
        buffer.push_back(static_cast<byte>(value >> 24));
        buffer.push_back(static_cast<byte>(value >> 16));
        buffer.push_back(static_cast<byte>(value >> 8));
        buffer.push_back(static_cast<byte>(value));
        return;
    }

    if (value < (1ull << 48))
    {
        buffer.push_back(0x86);
        buffer.push_back(static_cast<byte>(value >> 40));
        buffer.push_back(static_cast<byte>(value >> 32));
        buffer.push_back(static_cast<byte>(value >> 24));
        buffer.push_back(static_cast<byte>(value >> 16));
        buffer.push_back(static_cast<byte>(value >> 8));
        buffer.push_back(static_cast<byte>(value));
        return;
    }

    if (value < (1ull << 56))
    {
        buffer.push_back(0x87);
        buffer.push_back(static_cast<byte>(value >> 48));
        buffer.push_back(static_cast<byte>(value >> 40));
        buffer.push_back(static_cast<byte>(value >> 32));
        buffer.push_back(static_cast<byte>(value >> 24));
        buffer.push_back(static_cast<byte>(value >> 16));
        buffer.push_back(static_cast<byte>(value >> 8));
        buffer.push_back(static_cast<byte>(value));
        return;
    }

    buffer.push_back(0x88);
    buffer.push_back(static_cast<byte>(value >> 56));
    buffer.push_back(static_cast<byte>(value >> 48));
    buffer.push_back(static_cast<byte>(value >> 40));
    buffer.push_back(static_cast<byte>(value >> 32));
    buffer.push_back(static_cast<byte>(value >> 24));
    buffer.push_back(static_cast<byte>(value >> 16));
    buffer.push_back(static_cast<byte>(value >> 8));
    buffer.push_back(static_cast<byte>(value));
}

} // namespace abc::ethereum::rlp

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_RAW
