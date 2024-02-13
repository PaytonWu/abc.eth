// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/trie/compact_bytes.h>
#include <abc/ethereum/trie/nibble_bytes.h>

#include <gtest/gtest.h>

using namespace abc;
using namespace ethereum;
// using namespace trie;

TEST(compact_bytes, constructor)
{
    trie::nibble_bytes nibble_bytes{trie::nibble_bytes::from({0x01, 0x02, 0x03, 0x04, 0x05, 0x06})};
    trie::nibble_bytes_view view{nibble_bytes};

    {
        trie::nibble_bytes_view view1 = view;
        trie::compact_bytes compact_bytes{view1};
        
        ASSERT_EQ(7, compact_bytes.size());
        ASSERT_FALSE(compact_bytes.empty());
        ASSERT_EQ(0x20, compact_bytes.data()[0]);
        ASSERT_EQ(0x01, compact_bytes.data()[1]);
        ASSERT_EQ(0x02, compact_bytes.data()[2]);
        ASSERT_EQ(0x03, compact_bytes.data()[3]);
        ASSERT_EQ(0x04, compact_bytes.data()[4]);
        ASSERT_EQ(0x05, compact_bytes.data()[5]);
        ASSERT_EQ(0x06, compact_bytes.data()[6]);

        ASSERT_TRUE(leaf(compact_bytes.flag()));
        ASSERT_FALSE(extension(compact_bytes.flag()));
        ASSERT_TRUE(even(compact_bytes.flag()));
        ASSERT_FALSE(odd(compact_bytes.flag()));
    }

    {
        trie::nibble_bytes_view view2 = view.first(5);  // 0x00, 0x01, 0x00, 0x02, 0x00
        trie::compact_bytes compact_bytes{view2};

        ASSERT_EQ(3, compact_bytes.size());
        ASSERT_FALSE(compact_bytes.empty());

        ASSERT_EQ(0x10, compact_bytes.data()[0]);
        ASSERT_EQ(0x10, compact_bytes.data()[1]);
        ASSERT_EQ(0x20, compact_bytes.data()[2]);

        ASSERT_FALSE(leaf(compact_bytes.flag()));
        ASSERT_TRUE(extension(compact_bytes.flag()));
        ASSERT_FALSE(even(compact_bytes.flag()));
        ASSERT_TRUE(odd(compact_bytes.flag()));
    }

    {
        trie::nibble_bytes_view view3 = view.last(5);  // 0x00, 0x05, 0x00, 0x06, 0x10
        trie::compact_bytes compact_bytes{view3};

        ASSERT_EQ(3, compact_bytes.size());
        ASSERT_FALSE(compact_bytes.empty());

        ASSERT_EQ(0x20, compact_bytes.data()[0]);
        ASSERT_EQ(0x05, compact_bytes.data()[1]);
        ASSERT_EQ(0x06, compact_bytes.data()[2]);

        ASSERT_TRUE(leaf(compact_bytes.flag()));
        ASSERT_FALSE(extension(compact_bytes.flag()));
        ASSERT_TRUE(even(compact_bytes.flag()));
        ASSERT_FALSE(odd(compact_bytes.flag()));
    }

    {
        trie::nibble_bytes_view view4 = view.last(2);  // 0x06, 0x10
        trie::compact_bytes compact_bytes{view4};

        ASSERT_EQ(1, compact_bytes.size());
        ASSERT_FALSE(compact_bytes.empty());

        ASSERT_EQ(0x36, compact_bytes.data()[0]);

        ASSERT_TRUE(leaf(compact_bytes.flag()));
        ASSERT_FALSE(extension(compact_bytes.flag()));
        ASSERT_FALSE(even(compact_bytes.flag()));
        ASSERT_TRUE(odd(compact_bytes.flag()));
    }

    {
        trie::nibble_bytes_view view5 = view.subview(4, 4);  // 0x00, 0x03, 0x00, 0x04
        trie::compact_bytes compact_bytes{view5};

        ASSERT_EQ(3, compact_bytes.size());
        ASSERT_FALSE(compact_bytes.empty());

        ASSERT_EQ(0x00, compact_bytes.data()[0]);
        ASSERT_EQ(0x03, compact_bytes.data()[1]);
        ASSERT_EQ(0x04, compact_bytes.data()[2]);

        ASSERT_FALSE(leaf(compact_bytes.flag()));
        ASSERT_TRUE(extension(compact_bytes.flag()));
        ASSERT_TRUE(even(compact_bytes.flag()));
        ASSERT_FALSE(odd(compact_bytes.flag()));
    }

    {
        trie::nibble_bytes_view view6 = view.subview(4, 1);  // 0x00
        trie::compact_bytes compact_bytes{view6};

        ASSERT_EQ(1, compact_bytes.size());
        ASSERT_FALSE(compact_bytes.empty());

        ASSERT_EQ(0x10, compact_bytes.data()[0]);

        ASSERT_FALSE(leaf(compact_bytes.flag()));
        ASSERT_TRUE(extension(compact_bytes.flag()));
        ASSERT_FALSE(even(compact_bytes.flag()));
        ASSERT_TRUE(odd(compact_bytes.flag()));
    }
}
