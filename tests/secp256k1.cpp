// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/converter.h>
#include <abc/ethereum/crypto/secp256k1.h>
#include <abc/ethereum/types/bytes.h>

#include <gtest/gtest.h>

using namespace abc::ethereum;

// test data:
// address: 0xabcc7C1522EAf3d37928199b85df9732676836D6
// private key: c67a31aca1e2bad8469003930c6d08f80f5087720d2276d3c85ad74d3297adec

using namespace CryptoPP;

TEST(secp256k1, private_key_from_hex) {
    auto const & private_key_bytes_or_error = abc::hex_string::from("c67a31aca1e2bad8469003930c6d08f80f5087720d2276d3c85ad74d3297adec").and_then([](auto && hex_str) { return abc::convert_to<abc::bytes32_be_t>::from(hex_str); });
    ASSERT_TRUE(private_key_bytes_or_error.has_value());
    auto const & private_key_bytes = private_key_bytes_or_error.value();

    auto const & private_key_or_error = crypto::secp256k1::private_key::from(private_key_bytes);
    ASSERT_TRUE(private_key_or_error.has_value());

    auto const & private_key = private_key_or_error.value();
    ASSERT_EQ(private_key_bytes, private_key.bytes());
}