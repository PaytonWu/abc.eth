// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_ETH1_HEADER
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_ETH1_HEADER

#pragma once

#include <abc/ethereum/types/address.h>
#include <abc/fixed_bytes.h>
#include <abc/fixed_hash.h>
#include <abc/uint128.h>

namespace abc::ethereum::types::eth1 {

struct header {
    h256_t parent_hash;
    h256_t uncle_hash;
    address coinbase;
    h256_t state_root;
    h256_t transactions_root;
    h256_t receipts_root;
    bytes256_t logs_bloom;
    uint128_t difficulty;
    uint64_t number;
    uint64_t gas_limit;
    uint64_t gas_used;
    uint64_t timestamp;
    bytes_t extra_data;
    h256_t mix_hash;
    bytes8_be_t nonce;

    std::optional<uint128_t> base_fee_per_gas;
    std::optional<h256_t> withdrawals_root;
    std::optional<uint64_t> blob_gas_used;
    std::optional<uint64_t> excess_blob_gas;
    std::optional<h256_t> parent_beacon_block_root;

    friend
    auto
    operator==(header const & lhs, header const & rhs) noexcept -> bool = default;
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_ETH1_HEADER
