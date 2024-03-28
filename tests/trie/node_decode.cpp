// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/trie/node_decode.h>
#include <abc/bytes_view.h>

#include <gtest/gtest.h>
#include <range/v3/algorithm/fill.hpp>

#include <any>
#include <array>
#include <string_view>
#include <utility>

auto
new_test_full_node(std::any data) -> std::array<std::any, 17>
{
    std::array<std::any, 17> full_node_data;
    for (auto i = 0u; i < 16; ++i)
    {
        abc::bytes_t bytes;
        bytes.resize(32);
        ranges::fill(bytes, static_cast<uint8_t>(i + 1));
        full_node_data[i] = std::move(bytes);
    }

    full_node_data[16] = std::move(data);

    return full_node_data;
}

TEST(node_decode, decode_nested_node)
{
    std::string_view raw = "fullnode";
    abc::bytes_view_t input{raw };
    auto full_node_data = new_test_full_node(input);

    std::array<abc::bytes_t, 17> data;
    data[16] = abc::bytes_view_t{"subnode"};
    full_node_data[15] = data;


}