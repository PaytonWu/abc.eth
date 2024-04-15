// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_TESTS_TRIE_FULL_NODE_DATA)
#define ABC_ETH_TESTS_TRIE_FULL_NODE_DATA

#pragma once

#include <abc/ethereum/rlp/pack.h>

#include <abc/bytes_view.h>
#include <abc/fixed_bytes.h>

struct full_node_data
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
    abc::bytes32_t data15{};
    abc::bytes_t data16{};
};

void
init_full_node_data(full_node_data & fn_data, std::string_view data16)
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
    fn_data.data15.fill(16);
    fn_data.data16 = abc::bytes_view_t{data16};
}

namespace abc::ethereum::rlp::adaptor
{

template <>
struct as<full_node_data>
{
    auto
    operator()(rlp::object const & o) const -> full_node_data
    {
        if (o.type != rlp::type::list)
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::type_error));
        }

        if (o.data.array.size != 17)
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::type_error));
        }

        full_node_data v;

        v.data16 = o.data.array.ptr[16].as<abc::bytes_t>();
        v.data15 = o.data.array.ptr[15].as<abc::bytes32_t>();
        v.data14 = o.data.array.ptr[14].as<abc::bytes32_t>();
        v.data13 = o.data.array.ptr[13].as<abc::bytes32_t>();
        v.data12 = o.data.array.ptr[12].as<abc::bytes32_t>();
        v.data11 = o.data.array.ptr[11].as<abc::bytes32_t>();
        v.data10 = o.data.array.ptr[10].as<abc::bytes32_t>();
        v.data9 = o.data.array.ptr[9].as<abc::bytes32_t>();
        v.data8 = o.data.array.ptr[8].as<abc::bytes32_t>();
        v.data7 = o.data.array.ptr[7].as<abc::bytes32_t>();
        v.data6 = o.data.array.ptr[6].as<abc::bytes32_t>();
        v.data5 = o.data.array.ptr[5].as<abc::bytes32_t>();
        v.data4 = o.data.array.ptr[4].as<abc::bytes32_t>();
        v.data3 = o.data.array.ptr[3].as<abc::bytes32_t>();
        v.data2 = o.data.array.ptr[2].as<abc::bytes32_t>();
        v.data1 = o.data.array.ptr[1].as<abc::bytes32_t>();
        v.data0 = o.data.array.ptr[0].as<abc::bytes32_t>();

        return v;
    }
};

template <>
struct convert<full_node_data>
{
    auto
    operator()(rlp::object const & o, full_node_data & v) const -> rlp::object const &
    {
        v = as<full_node_data>{}(o);
        return o;
    }
};

template <>
struct pack<full_node_data>
{
    template <packing_stream Stream>
    auto
    operator()(packer<Stream> & o, full_node_data const & v) const -> packer<Stream> &
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

        return o;
    }
};

template <>
struct object<full_node_data>
{
    auto
    operator()(rlp::object &, full_node_data const &) const -> void
    {
    }
};

} // namespace abc::ethereum::rlp::adaptor

#endif // ABC_ETH_TESTS_TRIE_FULL_NODE_DATA
