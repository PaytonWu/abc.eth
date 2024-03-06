// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_RAW)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_RAW

#pragma once

#include "raw_decl.h"

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
            return static_cast<uint64_t>(head_size((static_cast<std::uint64_t>(sz))) + sz);
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
            return static_cast<uint64_t>(head_size((static_cast<std::uint64_t>(sz))) + sz);
    }
}

constexpr auto
list_size(std::uint64_t content_size) noexcept -> std::uint64_t
{
    return static_cast<uint64_t>(head_size(content_size)) + content_size;
}



} // namespace abc::ethereum::rlp

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_RAW
