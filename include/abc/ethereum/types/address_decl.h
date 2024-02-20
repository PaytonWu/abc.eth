// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if! defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_ADDRESS_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_ADDRESS_DECL

#pragma once

#include "address_fwd_decl.h"

#include <abc/byte.h>
#include <abc/ethereum/crypto/secp256k1.h>
#include <abc/expected.h>
#include <abc/fixed_bytes.h>
#include <abc/hex_string.h>

#include <compare>

namespace abc::ethereum::types
{

class address
{
public:
    static constexpr size_t length = 20;
    using value_type = fixed_bytes<length, byte_numbering::msb0>;

private:
    fixed_bytes<length, byte_numbering::msb0> raw_address_{};

private:
    explicit address(crypto::secp256k1::public_key const & public_key);
    explicit address(hex_string const & hex_string) noexcept;
    explicit address(value_type const & address_bytes) noexcept;

public:
    constexpr address() = default;

    static auto
    from(crypto::secp256k1::public_key const & public_key) -> address;

    static auto
    from(crypto::secp256k1::private_key const & private_key) -> expected<address, std::error_code>;

    static auto
    from(hex_string const & hex_string) -> expected<address, std::error_code>;

    static auto
    from(std::string_view hex_string) -> expected<address, std::error_code>;

    static auto
    from(value_type address_bytes) -> address;

    static auto
    from(bytes_be_view_t bytes) -> expected<address, std::error_code>;

    [[nodiscard]] constexpr auto
    bytes() const noexcept -> value_type const &;

    constexpr auto
    hex_string() const -> hex_string;

    static constexpr auto
    zero() -> address const &;

    constexpr friend auto
    operator==(address const & lhs, address const & rhs) noexcept -> bool = default;

    constexpr friend auto
    operator<=>(address const & lhs, address const & rhs) noexcept -> std::strong_ordering = default;
};

} // namespace abc::ethereum::types

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_ADDRESS_DECL
