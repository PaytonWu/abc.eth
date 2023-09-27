// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/converter.h>
#include <abc/ethereum/crypto/keccak.h>
#include <abc/ethereum/crypto/secp256k1.h>

#include <gtest/gtest.h>

using namespace abc::ethereum;

// test data:
// address: 0xabcc7C1522EAf3d37928199b85df9732676836D6
// private key: c67a31aca1e2bad8469003930c6d08f80f5087720d2276d3c85ad74d3297adec

TEST(keccak256, digest) {
    auto const & public_key_uncompressed_or_error = abc::hex_string::from("c67a31aca1e2bad8469003930c6d08f80f5087720d2276d3c85ad74d3297adec").and_then([](auto && hex_str) { return abc::convert_to<abc::bytes32_be_t>::from(hex_str); })
                                                                                                                                             .and_then([](auto && bytes) { return crypto::secp256k1::private_key::from(bytes); })
                                                                                                                                             .and_then([](auto && private_key) { return private_key.public_key(); })
                                                                                                                                             .transform([](auto && public_key) { return public_key.bytes(); });
    ASSERT_TRUE(public_key_uncompressed_or_error.has_value());
    auto const & public_key_bytes = public_key_uncompressed_or_error.value();
    std::span<abc::byte const> bytes = std::span<abc::byte const>{ std::next(std::begin(public_key_bytes), 1), std::end(public_key_bytes) };

    auto const & digest = crypto::keccak256_t::digest(bytes);
    ASSERT_EQ(0xd6, digest.back());
}