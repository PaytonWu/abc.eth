// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/types/address.h>
#include <abc/bytes.h>
#include <abc/ethereum/error.h>

#include <cryptopp/keccak.h>

#include <memory>

using namespace CryptoPP;

namespace abc::ethereum::types {

address::address(crypto::ecdsa::public_key_t const & public_key) {
    ECP::Point const & point = public_key.GetPublicElement();
    size_t size = point.x.ByteCount();

    bytes pubkey_bytes;
    pubkey_bytes.resize(size * 2);

    point.x.Encode(&pubkey_bytes[0], size);
    point.y.Encode(&pubkey_bytes[size], size);

    // Hash the public key using Keccak-256
    Keccak_256 hash;
    byte digest[32];
    hash.Update(pubkey_bytes.data(), size * 2);
    hash.Final(digest);

    // Take the last 20 bytes of the hash as the address
    std::memcpy(raw_address_.data(), digest + 12, 20);
}

address::address(abc::hex_string const & hex_string) noexcept : raw_address_{address_storage_t::from(hex_string.to_bytes<byte_numbering::msb0>()).value()} {
}

auto address::from(crypto::ecdsa::public_key_t const & public_key) -> expected<address, std::error_code> {
    return address{public_key};
}

auto address::from(abc::hex_string const & hex_string) -> expected<address, std::error_code> {
    if (hex_string.bytes_size() != length) {
        return make_unexpected(abc::ethereum::errc::invalid_address);
    }

    return address{hex_string};
}

auto address::from(std::string_view hex_string) -> expected<address, std::error_code> {
    return hex_string::from(hex_string).transform_error([](auto && ec) { return make_error_code(ec); }).and_then([](auto && hex_str) { return address::from(hex_str); });
}

}