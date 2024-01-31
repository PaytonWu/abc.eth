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
    EXPECT_TRUE(nb1.empty());
    EXPECT_FALSE(nb1.has_terminator());

    nibble_bytes nb2 = nibble_bytes::from({ 0x12, 0x34, 0x56, 0x78 });
    EXPECT_EQ(nb2.size(), 9);
    EXPECT_FALSE(nb2.empty());
    EXPECT_TRUE(nb2.has_terminator());
    EXPECT_EQ(nb2[0], 0x01);
    EXPECT_EQ(nb2[1], 0x02);
    EXPECT_EQ(nb2[2], 0x03);
    EXPECT_EQ(nb2[3], 0x04);
    EXPECT_EQ(nb2[4], 0x05);
    EXPECT_EQ(nb2[5], 0x06);
    EXPECT_EQ(nb2[6], 0x07);
    EXPECT_EQ(nb2[7], 0x08);
    EXPECT_EQ(nb2[8], 0x10);

    nibble_bytes nb3 = nibble_bytes::from({ 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0 });
    EXPECT_EQ(nb3.size(), 17);
    EXPECT_FALSE(nb3.empty());
    EXPECT_TRUE(nb3.has_terminator());
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

TEST(nibble_bytes, nibble_bytes_view)
{
    nibble_bytes nb1 = nibble_bytes::from({ 0x12, 0x34, 0x56, 0x78 });
    nibble_bytes_view nbv1{ nb1 };
    EXPECT_EQ(nbv1.size(), 9);
    EXPECT_FALSE(nbv1.empty());
    EXPECT_TRUE(nbv1.has_termintor());
    EXPECT_EQ(nbv1[0], 0x01);
    EXPECT_EQ(nbv1[1], 0x02);
    EXPECT_EQ(nbv1[2], 0x03);
    EXPECT_EQ(nbv1[3], 0x04);
    EXPECT_EQ(nbv1[4], 0x05);
    EXPECT_EQ(nbv1[5], 0x06);
    EXPECT_EQ(nbv1[6], 0x07);
    EXPECT_EQ(nbv1[7], 0x08);
    EXPECT_EQ(nbv1[8], 0x10);

    nibble_bytes nb2 = nibble_bytes::from({ 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0 });
    nibble_bytes_view nbv2{ nb2 };
    EXPECT_EQ(nbv2.size(), 17);
    EXPECT_FALSE(nbv2.empty());
    EXPECT_TRUE(nbv2.has_termintor());
    EXPECT_EQ(nbv2[0], 0x01);
    EXPECT_EQ(nbv2[1], 0x02);
    EXPECT_EQ(nbv2[2], 0x03);
    EXPECT_EQ(nbv2[3], 0x04);
    EXPECT_EQ(nbv2[4], 0x05);
    EXPECT_EQ(nbv2[5], 0x06);
    EXPECT_EQ(nbv2[6], 0x07);
    EXPECT_EQ(nbv2[7], 0x08);
    EXPECT_EQ(nbv2[8], 0x09);
    EXPECT_EQ(nbv2[9], 0x0A);
    EXPECT_EQ(nbv2[10], 0x0B);
    EXPECT_EQ(nbv2[11], 0x0C);
    EXPECT_EQ(nbv2[12], 0x0D);
    EXPECT_EQ(nbv2[13], 0x0E);
    EXPECT_EQ(nbv2[14], 0x0F);
    EXPECT_EQ(nbv2[15], 0x00);
    EXPECT_EQ(nbv2[16], 0x10);
}

TEST(nibble_bytes_view, subview)
{
    nibble_bytes nb1 = nibble_bytes::from({ 0x12, 0x34, 0x56, 0x78 });
    nibble_bytes_view nbv1{ nb1 };
    auto subview1 = nbv1.subview(2);
    EXPECT_EQ(subview1.size(), 7);
    EXPECT_FALSE(subview1.empty());
    EXPECT_TRUE(subview1.has_termintor());
    EXPECT_EQ(subview1[0], 0x03);
    EXPECT_EQ(subview1[1], 0x04);
    EXPECT_EQ(subview1[2], 0x05);
    EXPECT_EQ(subview1[3], 0x06);
    EXPECT_EQ(subview1[4], 0x07);
    EXPECT_EQ(subview1[5], 0x08);
    EXPECT_EQ(subview1[6], 0x10);

    auto subview2 = nbv1.subview(2, 2);
    EXPECT_EQ(subview2.size(), 2);
    EXPECT_FALSE(subview2.empty());
    EXPECT_FALSE(subview2.has_termintor());
    EXPECT_EQ(subview2[0], 0x03);
    EXPECT_EQ(subview2[1], 0x04);

    auto subview4 = nbv1.subview(4, 8);
    EXPECT_EQ(subview4.size(), 5);
    EXPECT_FALSE(subview4.empty());
    EXPECT_TRUE(subview4.has_termintor());
    EXPECT_EQ(subview4[0], 0x05);
    EXPECT_EQ(subview4[1], 0x06);
    EXPECT_EQ(subview4[2], 0x07);
    EXPECT_EQ(subview4[3], 0x08);
    EXPECT_EQ(subview4[4], 0x10);

    auto subview5 = nbv1.subview(4, 0);
    EXPECT_EQ(subview5.size(), 0);
    EXPECT_TRUE(subview5.empty());
    EXPECT_FALSE(subview5.has_termintor());
}
