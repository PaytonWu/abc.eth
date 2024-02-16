// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/types/address.h>
#include <abc/hex_string.h>

#include <gtest/gtest.h>

using namespace abc::ethereum;

// test data:
// address: 0xabcc7C1522EAf3d37928199b85df9732676836D6
// private key: c67a31aca1e2bad8469003930c6d08f80f5087720d2276d3c85ad74d3297adec

TEST(address, from_zero_address) {
    std::string_view raw_address = "0x0000000000000000000000000000000000000000";
    auto result = types::address::from(raw_address);
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value().hex_string().to_string(), raw_address);
}

TEST(address, from_nonzero_address) {
    abc::hex_string raw_address = abc::hex_string::from("0xffffffffffffffffffffffffffffffffffffffff").value();
    auto result = types::address::from(raw_address);
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result.value().hex_string(), raw_address);
}

TEST(address, from_private_key) {
    types::address::value_type const address_bytes = abc::hex_string::from("0xabcc7C1522EAf3d37928199b85df9732676836D6").transform([](auto && hex) { return hex.template bytes<abc::byte_numbering::msb0>(); })
                                                                                                                 .and_then([](auto && bytes) { return types::address::value_type::from<abc::byte_numbering::msb0>(bytes); })
                                                                                                                 .value();
    abc::expected<crypto::secp256k1::private_key, std::error_code> private_key_result = abc::hex_string::from("c67a31aca1e2bad8469003930c6d08f80f5087720d2276d3c85ad74d3297adec").and_then([](auto && hex) { return crypto::secp256k1::private_key::from(hex); });
    ASSERT_TRUE(private_key_result.has_value());

    auto const address_result = private_key_result.and_then([](auto && private_key) { return types::address::from(private_key); });
    ASSERT_TRUE(address_result.has_value());

    ASSERT_EQ(address_bytes, address_result.value().bytes());
}