// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETHEREUM_ETH1_TYPES_ADDRESS)
#define ABC_ETHEREUM_ETH1_TYPES_ADDRESS

#pragma once

#include "abc/fixed_bytes.h"
#include "abc/hex_string.h"
#include "abc/ethereum/error.h"

#include <expected>

namespace abc::ethereum::eth1::types {

class address : private fixed_bytes<20, byte_numbering::msb0> {
public:
    constexpr static auto size = 20;

    constexpr address() = default;
    constexpr address(address const &) = default;
    constexpr auto operator=(address const &) -> address & = default;
    constexpr address(address &&) = default;
    constexpr auto operator=(address &&) -> address & = default;
    ~address() = default;

private:
    constexpr address(std::array<byte, size> const & data) : fixed_bytes<size, byte_numbering::msb0>{data} {}

public:
    constexpr static auto from(hex_string const & hex_str) -> std::expected<address, errc> {
        if (hex_str.size() != size * 2) {
            return std::unexpected{errc::invalid_address};
        }

        return std::expected<address, errc>{ address{fixed_bytes<size, byte_numbering::msb0>::from(hex_str)} };
    }
};

#endif //ABC_ETHEREUM_ETH1_TYPES_ADDRESS
