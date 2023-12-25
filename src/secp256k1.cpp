// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/bytes_view.h>
#include <abc/ethereum/crypto/secp256k1.h>
#include <abc/ethereum/error.h>

#include <cryptopp/cryptlib.h>
#include <cryptopp/eccrypto.h>
#include <cryptopp/ecp.h>
#include <cryptopp/oids.h>
#include <cryptopp/osrng.h>
#include <cryptopp/secblock.h>
#include <cryptopp/sha.h>

#include <span>

using namespace CryptoPP;

namespace abc::ethereum::crypto::secp256k1 {

private_key::private_key(CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey const & pkey) : private_key_{ pkey } {
}

auto private_key::random() -> expected<private_key, std::error_code> {
    AutoSeededRandomPool prng;
    ECDSA<ECP, SHA256>::PrivateKey pkey;
    pkey.Initialize(prng, ASN1::secp256k1());
    bool result = pkey.Validate(prng, 3);
    if (!result) {
        return make_unexpected<std::error_code>(errc::invalid_private_key);
    }

    return private_key{ pkey };
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

auto private_key::bytes() const -> bytes32_be_t {
    auto const & exponent = private_key_.GetPrivateExponent();
    size_t key_size = exponent.MinEncodedSize();

    SecByteBlock private_key_bytes{key_size};
    exponent.Encode(private_key_bytes, key_size);

    return bytes32_be_t::from<byte_numbering::msb0>(bytes_be_view_t{ private_key_bytes.data(), private_key_bytes.size() }).value();
}

auto private_key::hex_string() const -> abc::hex_string {
    return hex_string::from<byte_numbering::msb0>(bytes());
}

auto private_key::public_key() const -> expected<secp256k1::public_key, std::error_code> {
    ECDSA<ECP, SHA256>::PublicKey pkey;
    private_key_.MakePublicKey(pkey);

    AutoSeededRandomPool rng;
    if (!pkey.Validate(rng, 3)) {
        return make_unexpected<std::error_code>(errc::invalid_public_key);
    }

    return secp256k1::public_key{ pkey };
}

public_key::public_key(CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey const & pkey) : public_key_{ pkey } {
}

auto public_key::from(secp256k1::private_key const & private_key) -> expected<secp256k1::public_key, std::error_code> {
    return private_key.public_key();
}

auto public_key::valid() const noexcept -> bool {
    return public_key_.Validate(NullRNG(), 3);
}

auto public_key::bytes() const -> bytes65_be_t {
    bytes65_be_t result;
    result[0] = 0x04;

    auto const & x = public_key_.GetPublicElement().x;
    auto const & y = public_key_.GetPublicElement().y;

    x.Encode(&result[1], 32);
    y.Encode(&result[33], 32);

    return result;
}

auto public_key::compact_bytes() const -> bytes33_be_t {
    bytes33_be_t result;

    auto const & x = public_key_.GetPublicElement().x;
    auto const & y = public_key_.GetPublicElement().y;

    result[0] = y.IsEven() ? 0x02 : 0x03;
    x.Encode(&result[1], 32);

    return result;
}

}
