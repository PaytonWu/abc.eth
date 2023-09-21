// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_CRYPTO_SECP256K1
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_CRYPTO_SECP256K1

#pragma once

#include "config.h"

#include <abc/expected.h>
#include <abc/fixed_bytes.h>
#include <abc/hex_string.h>

#include <cryptopp/eccrypto.h>

#include <string_view>

namespace abc::ethereum::crypto::secp256k1 {

class public_key;

class private_key {
private:
    CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey private_key_;

    explicit private_key(CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey const & pkey);

public:
    static auto random() -> expected<private_key, std::error_code>;
    static auto from(bytes32_be_t const & bytes) -> expected<private_key, std::error_code>;
    static auto from(std::span<byte const> bytes) -> expected<private_key, std::error_code>;
    static auto from(hex_string const & hex_string) -> expected<private_key, std::error_code>;
    static auto from(std::string_view hex_string) -> expected<private_key, std::error_code>;

    auto bytes() const -> bytes32_be_t;
    auto hex_string() const -> abc::hex_string;

    auto public_key() const -> expected<secp256k1::public_key, std::error_code>;
};

class public_key {
private:
    friend class private_key;
    CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey public_key_;

    explicit public_key(CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey const & pkey);

public:
    static auto from(private_key const & private_key) -> expected<secp256k1::public_key, std::error_code>;

    auto valid() const noexcept -> bool;

    auto bytes() const -> bytes65_be_t;
    auto compact_bytes() const -> bytes33_be_t;
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_CRYPTO_SECP256K1
