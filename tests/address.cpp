// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/types/address.h>

#include <gtest/gtest.h>

using namespace abc::ethereum;

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