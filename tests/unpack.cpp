// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/rlp/pack.h>
#include <abc/ethereum/rlp/sbuffer.h>
#include <abc/ethereum/types/eth1/header.h>
#include <abc/fixed_hash.h>
#include <abc/uint128.h>

#include <gtest/gtest.h>

TEST(unpack, eth_header) {
    using namespace abc::ethereum::types;
    using namespace abc::ethereum::rlp;

    eth1::header header{
        .parent_hash = abc::h256_t{},
        .uncle_hash = abc::h256_t{},
        .coinbase = address::zero(),
        .state_root = abc::h256_t{},
        .transactions_root = abc::h256_t{},
        .receipts_root = abc::h256_t{},
        .logs_bloom = abc::bytes32_t{},
        .difficulty = abc::uint128_t{},
        .number = 0,
        .gas_limit = 0,
        .gas_used = 0,
        .timestamp = 0,
        .extra_data = abc::bytes_t{},
        .mix_hash = abc::h256_t{},
        .nonce = abc::bytes8_t{},
        .base_fee_per_gas = std::nullopt,
        .withdrawals_root = std::nullopt,
        .blob_gas_used = std::nullopt,
        .excess_blob_gas = std::nullopt,
        .parent_beacon_block_root = std::nullopt
    };

    sbuffer buffer{};
    packer<sbuffer> packer{ buffer };

    packer.pack(header);
}
