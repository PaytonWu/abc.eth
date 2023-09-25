// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/rlp/zone/allocator.h>

#include <gtest/gtest.h>

using namespace abc::ethereum::rlp::zone;

TEST(allocator, allocate_aligned_with_aligned_size) {
    {
        allocator alloc{ 1024 };
        EXPECT_EQ(1024, alloc.unused_size());

        auto * ptr = alloc.allocate<aligned, alignof(int)>(512);
        EXPECT_NE(nullptr, ptr);
        EXPECT_TRUE(reinterpret_cast<std::uintptr_t>(ptr) % alignof(int) == 0);
        EXPECT_EQ(alloc.unused_size(), 512);

        ptr = alloc.allocate<aligned, alignof(int)>(512);
        EXPECT_NE(nullptr, ptr);
        EXPECT_TRUE(reinterpret_cast<std::uintptr_t>(ptr) % alignof(int) == 0);
        EXPECT_EQ(alloc.unused_size(), 0);
    }
}

TEST(allocator, allocate_aligned_with_unaligned_size) {
    {
        allocator alloc{ 1024 };

        auto * ptr = alloc.allocate<unaligned>(511);
        EXPECT_NE(nullptr, ptr);
        EXPECT_EQ(alloc.unused_size(), 513);    // unused = 1024 - 511 = 513

        ptr = alloc.allocate<unaligned>(510);
        EXPECT_NE(nullptr, ptr);
        EXPECT_EQ(alloc.unused_size(), 3);  // unused = 513 - 510 = 3
    }

    {
        allocator alloc{ 1024 };

        auto * ptr = alloc.allocate<unaligned>(510);
        EXPECT_NE(nullptr, ptr);
        EXPECT_EQ(alloc.unused_size(), 514);    // unused = 1024 - 510 = 514

        ptr = alloc.allocate<unaligned>(509);
        EXPECT_NE(nullptr, ptr);
        EXPECT_EQ(alloc.unused_size(), 5);  // unused = 514 - 509 = 5
    }

    {
        allocator alloc{ 1024 };

        auto * ptr = alloc.allocate<unaligned>(509);
        EXPECT_NE(nullptr, ptr);
        EXPECT_EQ(alloc.unused_size(), 515);    // unused = 1024 - 509 = 515

        ptr = alloc.allocate<unaligned>(509);
        EXPECT_NE(nullptr, ptr);
        EXPECT_EQ(alloc.unused_size(), 6);  // unused = 515 - 509 = 6
    }
}

TEST(allocator, deallocate) {
    {
        allocator alloc{ 1024 };
        EXPECT_EQ(1024, alloc.unused_size());

        auto * ptr1 = alloc.allocate<aligned, alignof(int)>(512);
        alloc.deallocate(512);
        auto * ptr2 = alloc.allocate<aligned, alignof(int)>(512);

        EXPECT_EQ(ptr1, ptr2);
    }

    {
        allocator alloc{ 1024 };
        EXPECT_EQ(1024, alloc.unused_size());

        auto * ptr1 = alloc.allocate<unaligned>(17);
        alloc.deallocate(17);
        auto * ptr2 = alloc.allocate<unaligned>(17);

        EXPECT_EQ(ptr1, ptr2);
    }
}