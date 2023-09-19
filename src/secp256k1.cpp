// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/crypto/secp256k1.h>
#include <abc/ethereum/error.h>

#include <cryptopp/oids.h>
#include <cryptopp/osrng.h>
#include <cryptopp/secblock.h>
#include <cryptopp/hex.h>

#include <cryptopp/cryptlib.h>
#include <cryptopp/eccrypto.h>
#include <cryptopp/ecp.h>
#include <cryptopp/osrng.h>
#include <cryptopp/oids.h>
#include <cryptopp/sha.h>
#include <cryptopp/secblock.h>

#include <span>

using namespace CryptoPP;

namespace abc::ethereum::crypto::secp256k1 {

private_key::private_key(CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey const & pkey) : private_key_{ pkey } {
}

private_key::private_key() {
    AutoSeededRandomPool prng;
    private_key_.Initialize(prng, ASN1::secp256k1());
}

auto private_key::from(bytes32_be_t const & bytes) -> expected<private_key, std::error_code> {
    ECDSA<ECP, SHA256>::PrivateKey pkey;
    AutoSeededRandomPool rng;

    Integer privateKeyInt(bytes.data(), bytes.size());
    pkey.Initialize(rng, ASN1::secp256k1());
    pkey.SetPrivateExponent(privateKeyInt);
    if (!pkey.Validate(rng, 3)) {
        return make_unexpected(make_error_code(errc::invalid_private_key));
    }

    return private_key{ pkey };
}

auto private_key::from(std::span<byte const> bytes) -> expected<private_key, std::error_code> {
    if (bytes.size() != 32zu) {
        return make_unexpected(make_error_code(ethereum::errc::invalid_private_key_length));
    }

    ECDSA<ECP, SHA256>::PrivateKey pkey;
    AutoSeededRandomPool rng;

    Integer privateKeyInt(bytes.data(), bytes.size());
    pkey.Initialize(rng, ASN1::secp256k1());
    pkey.SetPrivateExponent(privateKeyInt);
    if (!pkey.Validate(rng, 3)) {
        return make_unexpected(make_error_code(errc::invalid_private_key));
    }

    return private_key{ pkey };
}

auto private_key::from(abc::hex_string const & hex_string) -> expected<private_key, std::error_code> {
    if (hex_string.bytes_size() != 32zu) {
        return make_unexpected(make_error_code(errc::invalid_private_key_length));
    }

    auto const & raw_key = hex_string.bytes<byte_numbering::msb0>();
    Integer x;
    x.Decode(raw_key.data(), raw_key.size());

    ECDSA<ECP, SHA256>::PrivateKey pkey;
    pkey.Initialize(ASN1::secp256k1(), x);
    AutoSeededRandomPool rng;
    if (!pkey.Validate(rng, 3)) {
        return make_unexpected(make_error_code(errc::invalid_private_key));
    }

    return private_key{ pkey };
}

auto private_key::from(std::string_view hex_str) -> expected<private_key, std::error_code> {
    return hex_string::from(hex_str).and_then([](auto && hex) { return private_key::from(hex); });
}

auto private_key::bytes() const -> expected<bytes32_be_t, std::error_code> {
    if (!valid()) {
        return make_unexpected(make_error_code(errc::invalid_private_key));
    }

    auto const & exponent = private_key_.GetPrivateExponent();
    size_t key_size = exponent.MinEncodedSize();

    SecByteBlock private_key_bytes{key_size};
    exponent.Encode(private_key_bytes, key_size);

    return bytes32_be_t::from<byte_numbering::msb0>(private_key_bytes).value();
}

auto private_key::hex_string() const -> expected<abc::hex_string, std::error_code> {
    return bytes().transform([](auto && bytes32_be) { return hex_string::from<byte_numbering::msb0>(bytes32_be); });
}

auto private_key::valid() const noexcept -> bool {
    AutoSeededRandomPool rng;
    return private_key_.Validate(rng, 3);
}

}