// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/rlp/zone/arena.h>
#include <abc/ethereum/rlp/zone/allocator.h>

#include <gtest/gtest.h>

using namespace abc::ethereum::rlp::zone;

TEST(arena, default_constructor) {
    ASSERT_NO_THROW(arena<allocator> arena{});
}