// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/trie/node_decode.h>
#include <abc/ethereum/rlp/simple_buffer.h>
#include <abc/ethereum/rlp/pack.h>
#include <abc/bytes_view.h>

#include <gtest/gtest.h>
#include <range/v3/algorithm/fill.hpp>

#include <any>
#include <array>
#include <string_view>
#include <utility>
#include <variant>
#include <memory>

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

struct full_node_data_1
{
    abc::bytes32_t data0{};
    abc::bytes32_t data1{};
    abc::bytes32_t data2{};
    abc::bytes32_t data3{};
    abc::bytes32_t data4{};
    abc::bytes32_t data5{};
    abc::bytes32_t data6{};
    abc::bytes32_t data7{};
    abc::bytes32_t data8{};
    abc::bytes32_t data9{};
    abc::bytes32_t data10{};
    abc::bytes32_t data11{};
    abc::bytes32_t data12{};
    abc::bytes32_t data13{};
    abc::bytes32_t data14{};
    std::array<abc::bytes_t, 17> data15{};
    abc::bytes_t data16{};
};

void init_full_node_data_1(full_node_data_1 & fn_data, std::string_view data15, std::string_view data16)
{
    fn_data.data0.fill(1);
    fn_data.data1.fill(2);
    fn_data.data2.fill(3);
    fn_data.data3.fill(4);
    fn_data.data4.fill(5);
    fn_data.data5.fill(6);
    fn_data.data6.fill(7);
    fn_data.data7.fill(8);
    fn_data.data8.fill(9);
    fn_data.data9.fill(10);
    fn_data.data10.fill(11);
    fn_data.data11.fill(12);
    fn_data.data12.fill(13);
    fn_data.data13.fill(14);
    fn_data.data14.fill(15);
    fn_data.data15[16] = abc::bytes_view_t{data15};
    fn_data.data16 = abc::bytes_view_t{data16};
}

namespace abc::ethereum::rlp::adaptor
{

template <>
struct as<full_node_data_1>
{
    auto
    operator()(rlp::object const & o) const -> full_node_data_1;
};

template <>
struct convert<full_node_data_1>
{
    auto
    operator()(rlp::object const & o, full_node_data_1 & v) const -> rlp::object const &;
};

template <>
struct pack<full_node_data_1>
{
    template <packing_stream Stream>
    auto
    operator()(packer<Stream> & o, full_node_data_1 const & v) const -> packer<Stream> &
    {
        o.pack(v.data0);
        o.pack(v.data1);
        o.pack(v.data2);
        o.pack(v.data3);
        o.pack(v.data4);
        o.pack(v.data5);
        o.pack(v.data6);
        o.pack(v.data7);
        o.pack(v.data8);
        o.pack(v.data9);
        o.pack(v.data10);
        o.pack(v.data11);
        o.pack(v.data12);
        o.pack(v.data13);
        o.pack(v.data14);
        o.pack(v.data15);
        o.pack(v.data16);
    }
};

template <>
struct object<full_node_data_1>
{
    auto
    operator()(rlp::object& , full_node_data_1 const & ) const -> void;
};

}

TEST(node_decode, decode_nested_node)
{
    full_node_data_1 fn_data;
    fn_data.data0.fill(1);
    fn_data.data1.fill(2);
    fn_data.data2.fill(3);
    fn_data.data3.fill(4);
    fn_data.data4.fill(5);
    fn_data.data5.fill(6);
    fn_data.data6.fill(7);
    fn_data.data7.fill(8);
    fn_data.data8.fill(9);
    fn_data.data9.fill(10);
    fn_data.data10.fill(11);
    fn_data.data11.fill(12);
    fn_data.data12.fill(13);
    fn_data.data13.fill(14);
    fn_data.data14.fill(15);
    fn_data.data16 = abc::bytes_view_t{"fullnode"};
    fn_data.data15[16] = abc::bytes_view_t{"subnode"};

    abc::ethereum::rlp::simple_buffer buf;
    abc::ethereum::rlp::packer packer{ buf };

}