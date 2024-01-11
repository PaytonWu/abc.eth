// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/converter.h>
#include <abc/ethereum/rlp/adaptor/adaptor.h>
#include <abc/ethereum/rlp/object.h>
#include <abc/ethereum/rlp/unpack.h>
#include <abc/ethereum/types/eth1/header.h>
#include <abc/expected.h>
#include <abc/hex_string.h>

#include <gtest/gtest.h>

using namespace abc::ethereum::rlp;

TEST(unpack, unpack_function)
{
    abc::ethereum::types::eth1::header expected_header
    {
        .parent_hash = abc::hex_string::from("0x1e77d8f1267348b516ebc4f4da1e2aa59f85f0cbd853949500ffac8bfc38ba14").and_then([](auto && hexstr) { return abc::convert_to<abc::h256_t>::from(hexstr); }).value(),
        .uncle_hash = abc::hex_string::from("0x1dcc4de8dec75d7aab85b567b6ccd41ad312451b948a7413f0a142fd40d49347").and_then([](auto && hexstr) { return abc::convert_to<abc::h256_t>::from(hexstr); }).value(),
        .coinbase = abc::hex_string::from("0x2a65Aca4D5fC5B5C859090a6c34d164135398226").and_then([](auto && hexstr) { return abc::ethereum::types::address::from(hexstr); }).value(),
        .state_root = abc::hex_string::from("0x0b5e4386680f43c224c5c037efc0b645c8e1c3f6b30da0eec07272b4e6f8cd89").and_then([](auto && hexstr) { return abc::convert_to<abc::h256_t>::from(hexstr); }).value(),
        .transactions_root = abc::hex_string::from("0x56e81f171bcc55a6ff8345e692c0f86e5b48e01b996cadc001622fb5e363b421").and_then([](auto && hexstr) { return abc::convert_to<abc::h256_t>::from(hexstr); }).value(),
        .receipts_root = abc::hex_string::from("0x56e81f171bcc55a6ff8345e692c0f86e5b48e01b996cadc001622fb5e363b421").and_then([](auto && hexstr) { return abc::convert_to<abc::h256_t>::from(hexstr); }).value(),
        .logs_bloom = abc::bytes256_t{},
        .difficulty = abc::uint128_t{6022643743806ull},
        .number = 400000ull,
        .gas_limit = 3141592,
        .gas_used = 0,
        .timestamp = 1445130204,
        .extra_data = abc::hex_string::from("0xd583010202844765746885676f312e35856c696e7578").transform([](auto && hexstr) { return hexstr.template bytes<abc::byte_numbering::msb0>().template to<abc::byte_numbering::none>(); }).value(),
        .mix_hash = abc::hex_string::from("0x3fbea7af642a4e20cd93a945a1f5e23bd72fc5261153e09102cf718980aeff38").and_then([](auto && hexstr) { return abc::convert_to<abc::h256_t>::from(hexstr); }).value(),
        .nonce = abc::hex_string::from("0x6af23caae95692ef").and_then([](auto && hexstr) { return abc::convert_to<abc::bytes8_be_t>::from(hexstr); }).value(),
        .base_fee_per_gas = std::nullopt,
        .withdrawals_root = std::nullopt,
        .blob_gas_used = std::nullopt,
        .excess_blob_gas = std::nullopt,
        .parent_beacon_block_root = std::nullopt
    };

    auto const rlp_in_hex = abc::hex_string::from(
        "0xf90213a01e77d8f1267348b516ebc4f4da1e2aa59f85f0cbd853949500ffac8bfc38ba14a01dcc4de8dec75d7aab85b567b6ccd41ad312451b948a7413f0a142fd40d49347942a65aca4d5fc5b5c859090a6c34d164135398226a00b5e4386680f43c224c5c037efc0b645c8e1c3f6b30da0eec07272b4e6f8cd89a056e81f171bcc55a6ff8345e692c0f86e5b48e01b996cadc001622fb5e363b421a056e81f171bcc55a6ff8345e692c0f86e5b48e01b996cadc001622fb5e363b421b901000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000086057a418a7c3e83061a80832fefd880845622efdc96d583010202844765746885676f312e35856c696e7578a03fbea7af642a4e20cd93a945a1f5e23bd72fc5261153e09102cf718980aeff38886af23caae95692ef").value();
    auto const & bytes = rlp_in_hex.bytes<abc::byte_numbering::msb0>();
    abc::bytes_view_t view{ bytes.data(), bytes.size() };
    auto r = unpack(view);
    ASSERT_TRUE(r.has_value());
    auto const & o = r.value().get();
    ASSERT_EQ(o.type, type::list);
    auto const & header = o.as<abc::ethereum::types::eth1::header>();
    ASSERT_EQ(expected_header, header);
}