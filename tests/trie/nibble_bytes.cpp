// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/trie/nibble_bytes.h>

#include <gtest/gtest.h>

using namespace abc;
using namespace ethereum;
using namespace trie;

TEST(nibble_bytes, ctor)
{
    nibble_bytes nb1;
    EXPECT_EQ(nb1.size(), 0);
    EXPECT_EQ(nb1.empty(), true);

    nibble_bytes nb2{ 0x12, 0x34, 0x56, 0x78 };
    EXPECT_EQ(nb2.size(), 9);
    EXPECT_EQ(nb2.empty(), false);
    EXPECT_EQ(nb2[0], 0x01);
    EXPECT_EQ(nb2[1], 0x02);
    EXPECT_EQ(nb2[2], 0x03);
    EXPECT_EQ(nb2[3], 0x04);
    EXPECT_EQ(nb2[4], 0x05);
    EXPECT_EQ(nb2[5], 0x06);
    EXPECT_EQ(nb2[6], 0x07);
    EXPECT_EQ(nb2[7], 0x08);
    EXPECT_EQ(nb2[8], 0x10);

    nibble_bytes nb3{ 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0 };
    EXPECT_EQ(nb3.size(), 17);
    EXPECT_EQ(nb3.empty(), false);
    EXPECT_EQ(nb3[0], 0x01);
    EXPECT_EQ(nb3[1], 0x02);
    EXPECT_EQ(nb3[2], 0x03);
    EXPECT_EQ(nb3[3], 0x04);
    EXPECT_EQ(nb3[4], 0x05);
    EXPECT_EQ(nb3[5], 0x06);
    EXPECT_EQ(nb3[6], 0x07);
    EXPECT_EQ(nb3[7], 0x08);
    EXPECT_EQ(nb3[8], 0x09);
    EXPECT_EQ(nb3[9], 0x0A);
    EXPECT_EQ(nb3[10], 0x0B);
    EXPECT_EQ(nb3[11], 0x0C);
    EXPECT_EQ(nb3[12], 0x0D);
    EXPECT_EQ(nb3[13], 0x0E);
    EXPECT_EQ(nb3[14], 0x0F);
    EXPECT_EQ(nb3[15], 0x00);
    EXPECT_EQ(nb3[16], 0x10);
}
