// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_ADDRESS
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_ADDRESS

#pragma once

#include <abc/byte.h>
#include <abc/fixed_bytes.h>
#include <abc/expected.h>
#include <abc/ethereum/crypto/ecdsa.h>
#include <abc/hex_string.h>

#include <array>
#include <span>

namespace abc::ethereum::types {

using bytes20_t = fixed_bytes<20, byte_numbering::msb0>;

class address {
public:
    static constexpr size_t length = 20;

private:
    bytes20_t raw_address_;

private:
    explicit address(crypto::ecdsa::public_key_t const & public_key);
    explicit address(hex_string const & hex_string) noexcept;
    explicit address(bytes20_t const & address_bytes) noexcept;

public:
    static auto from(crypto::ecdsa::public_key_t const & public_key) -> expected<address, std::error_code>;
    static auto from(hex_string const & hex_string) -> expected<address, std::error_code>;
    static auto from(std::string_view hex_string) -> expected<address, std::error_code>;
    static auto from(bytes20_t address_bytes) -> address;

    [[nodiscard]] constexpr auto data() const noexcept -> bytes20_t const & {
        return raw_address_;
    }

    constexpr auto hex_string() const -> hex_string {
        return abc::hex_string::from<byte_numbering::msb0>(raw_address_);
    }

    template <typename SerializeStream>
    friend auto operator<<(SerializeStream & serialize_stream, address const & address) -> SerializeStream & {
        serialize_stream << address.data();
        return serialize_stream;
    }

    template <typename DeserializeStream>
    friend auto operator>>(DeserializeStream & deserialize_stream, address & address) -> DeserializeStream & {
        deserialize_stream >> const_cast<bytes20_t &>(address.data());
        return deserialize_stream;
    }
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_ADDRESS
