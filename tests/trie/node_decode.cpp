// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "full_node_data.h"
#include "full_node_wrong_nested_full_node.h"
#include "full_node_wrong_size.h"
#include "nested_full_node_data.h"

#include <abc/ethereum/trie/rlp/node_decode.h>

#include <abc/ethereum/rlp/pack.h>
#include <abc/ethereum/rlp/simple_buffer.h>

#include <gtest/gtest.h>

TEST(node_decode, nested_node)
{
    nested_full_node_data fn_data;
    init_nest_full_node_data(fn_data, "subnode", "fullnode");

    abc::ethereum::rlp::simple_buffer buf;
    abc::ethereum::rlp::packer packer{buf};
    packer.pack(fn_data);

    auto r = abc::ethereum::trie::rlp::decode_node(abc::h256_t::from(abc::bytes_view_t{"0123456789abcdef0123456789abcdef"}).value(), buf.bytes_view());
    ASSERT_TRUE(r.has_value());
}

TEST(node_decode, full_node_wrong_size_child)
{
    full_node_data_wrong_size fn_data;
    init_full_node_data_wrong_size(fn_data, "00", "wrongsizedchild");

    abc::ethereum::rlp::simple_buffer buf;
    abc::ethereum::rlp::packer packer{buf};
    packer.pack(fn_data);

    auto r = abc::ethereum::trie::rlp::decode_node(abc::h256_t::from(abc::bytes_view_t{"0123456789abcdef0123456789abcdef"}).value(), buf.bytes_view());
    ASSERT_FALSE(r.has_value());
}

TEST(node_decode, full_node_wrong_nested_full_node_data)
{
    std::array<abc::bytes_t, 17> data15;
    for (auto & data : data15)
    {
        data = abc::bytes_view_t{"123456"};
    }
    data15[16] = abc::bytes_view_t{"subnode"};

    full_node_wrong_nested_full_node_data fn_data;
    init_full_node_wrong_nested_full_node_data(fn_data, data15, "fullnode");

    abc::ethereum::rlp::simple_buffer buf;
    abc::ethereum::rlp::packer packer{buf};
    packer.pack(fn_data);

    auto r = abc::ethereum::trie::rlp::decode_node(abc::h256_t::from(abc::bytes_view_t{"0123456789abcdef0123456789abcdef"}).value(), buf.bytes_view());
    ASSERT_FALSE(r.has_value());
}

TEST(node_decode, full_node)
{
    full_node_data fn_data;
    init_full_node_data(fn_data, "fullnode");

    abc::ethereum::rlp::simple_buffer buf;
    abc::ethereum::rlp::packer packer{buf};
    packer.pack(fn_data);

    auto r = abc::ethereum::trie::rlp::decode_node(abc::h256_t::from(abc::bytes_view_t{"0123456789abcdef0123456789abcdef"}).value(), buf.bytes_view());
    ASSERT_TRUE(r.has_value());
}
