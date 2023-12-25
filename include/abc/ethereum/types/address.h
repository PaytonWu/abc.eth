// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_ADDRESS
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_ADDRESS

#pragma once

#include <abc/byte.h>
#include <abc/fixed_bytes.h>
#include <abc/expected.h>
#include <abc/ethereum/crypto/secp256k1.h>
#include <abc/hex_string.h>

#include <array>
#include <span>

namespace abc::ethereum::types {

using bytes20_be_t = fixed_bytes<20, byte_numbering::msb0>;

class [[nodiscard]] address {
public:
    static constexpr size_t length = 20;

private:
    fixed_bytes<length, byte_numbering::msb0> raw_address_{};

private:
    constexpr address() = default;

    explicit address(crypto::secp256k1::public_key const & public_key);
    explicit address(hex_string const & hex_string) noexcept;
    explicit address(bytes20_be_t const & address_bytes) noexcept;

public:
    // static constexpr address zero{};

    static auto from(crypto::secp256k1::public_key const & public_key) -> address;
    static auto from(crypto::secp256k1::private_key const & private_key) -> expected<address, std::error_code>;
    static auto from(hex_string const & hex_string) -> expected<address, std::error_code>;
    static auto from(std::string_view hex_string) -> expected<address, std::error_code>;
    static auto from(fixed_bytes<address::length, byte_numbering::msb0> address_bytes) -> address;

    [[nodiscard]] constexpr auto bytes() const noexcept -> fixed_bytes<address::length, byte_numbering::msb0> const & {
        return raw_address_;
    }

    constexpr auto hex_string() const -> hex_string {
        return abc::hex_string::from<byte_numbering::msb0>(raw_address_);
    }

    static constexpr auto zero() -> address const & {
        static constexpr address zero_address{};
        return zero_address;
    }

    template <typename SerializeStream>
    friend auto operator<<(SerializeStream & serialize_stream, address const & address) -> SerializeStream & {
        serialize_stream << address.bytes();
        return serialize_stream;
    }

    template <typename DeserializeStream>
    friend auto operator>>(DeserializeStream & deserialize_stream, address & address) -> DeserializeStream & {
        deserialize_stream >> const_cast<bytes20_be_t &>(address.bytes());
        return deserialize_stream;
    }
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_ADDRESS
