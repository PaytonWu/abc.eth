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
        
        ASSERT_EQ(compact_bytes.size(), 4);
        ASSERT_EQ(compact_bytes.data()[0], 0x21);
        ASSERT_EQ(compact_bytes.data()[1], 0x23);
        ASSERT_EQ(compact_bytes.data()[2], 0x45);
        ASSERT_EQ(compact_bytes.data()[3], 0x67);
    }
}
