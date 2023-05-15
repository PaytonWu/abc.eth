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

class address {
public:
    static constexpr size_t length = 20;

private:
    using address_storage_t = fixed_bytes<length, byte_numbering::none>;
    address_storage_t raw_address_;

private:
    explicit address(crypto::ecdsa::public_key_t const & public_key);
    explicit address(hex_string const & hex_string) noexcept;

public:
    static auto from(crypto::ecdsa::public_key_t const & public_key) -> expected<address, std::error_code>;
    static auto from(hex_string const & hex_string) -> expected<address, std::error_code>;
    static auto from(std::string_view hex_string) -> expected<address, std::error_code>;
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_ADDRESS
