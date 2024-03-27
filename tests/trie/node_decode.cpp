// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/trie/node_decode.h>
#include <abc/bytes_view.h>

#include <gtest/gtest.h>

#include <array>
#include <string_view>

auto
new_test_full_node(abc::bytes_view_t data) -> std::array<abc::bytes_t, 17>
{
    std::array<abc::bytes_t, 17> full_node_data{
        abc::bytes_t{ 0x01 }, abc::bytes_t{ 0x02 }, abc::bytes_t{ 0x03 }, abc::bytes_t{ 0x04 }, abc::bytes_t{ 0x05 },
        abc::bytes_t{ 0x06 }, abc::bytes_t{ 0x07 }, abc::bytes_t{ 0x08 }, abc::bytes_t{ 0x09 }, abc::bytes_t{ 0x0a },
        abc::bytes_t{ 0x0b }, abc::bytes_t{ 0x0c }, abc::bytes_t{ 0x0d }, abc::bytes_t{ 0x0e },
        abc::bytes_t{ 0x0f }, abc::bytes_t{ 0x10 }
    };

    full_node_data[16] = data;

    return full_node_data;
}

TEST(node_decode, decode_nested_node)
{
    std::string_view raw = "fullnode";
    abc::bytes_view_t input{raw };
    auto full_node_data = new_test_full_node(input);

    std::array<abc::bytes_t, 17> data;
    data[16] = abc::bytes_view_t{"subnode"};
    // full_node_data[15] = data;
}