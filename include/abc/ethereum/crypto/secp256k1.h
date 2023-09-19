// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_CRYPTO_SECP256K1
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_CRYPTO_SECP256K1

#pragma once

#include <abc/expected.h>
#include <abc/fixed_bytes.h>
#include <abc/hex_string.h>

#include <cryptopp/eccrypto.h>

#include <string_view>

namespace abc::ethereum::crypto::secp256k1 {

class private_key {
private:
    CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey private_key_;

    explicit private_key(CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey const & pkey);

public:
    private_key();

    static auto from(bytes32_be_t const & bytes) -> expected<private_key, std::error_code>;
    static auto from(std::span<byte const> bytes) -> expected<private_key, std::error_code>;
    static auto from(hex_string const & hex_string) -> expected<private_key, std::error_code>;
    static auto from(std::string_view hex_string) -> expected<private_key, std::error_code>;

    auto bytes() const -> expected<bytes32_be_t, std::error_code>;
    auto hex_string() const -> expected<abc::hex_string, std::error_code>;

    auto valid() const noexcept -> bool;
};

class public_key {
private:
    CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey public_key_;

public:
    static auto from(private_key const & private_key) -> expected<public_key, std::error_code>;
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_CRYPTO_SECP256K1
