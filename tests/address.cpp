// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/types/address.h>

#include <gtest/gtest.h>

using namespace abc::ethereum;

TEST(address, from) {
    auto result = types::address::from("0x0000000000000000000000000000000000000000");
    EXPECT_TRUE(result.has_value());
}