// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/types/eth1/header.h>
#include <abc/ethereum/rlp/pack.h>
#include <abc/ethereum/rlp/sbuffer.h>

namespace abc::ethereum::types::eth1 {

/*
 * struct header {
    h256_t parent_hash;
    h256_t uncle_hash;
    address coinbase;
    h256_t state_root;
    h256_t transactions_root;
    h256_t receipts_root;
    bytes32_t logs_bloom;
    uint128_t difficulty;
    uint64_t number;
    uint64_t gas_limit;
    uint64_t gas_used;
    uint64_t timestamp;
    bytes_t extra_data;
    h256_t mix_hash;
    bytes8_t nonce;

    std::optional<uint128_t> base_fee_per_gas;
    std::optional<h256_t> withdrawals_root;
    std::optional<uint64_t> blob_gas_used;
    std::optional<uint64_t> excess_blob_gas;
    std::optional<h256_t> parent_beacon_block_root;
};
 */
auto pack(header const & h) -> bytes_t {
    bytes_t ret;
    ret.reserve(h.parent_hash.size() + h.uncle_hash.size() + h.coinbase.length + h.state_root.size() + h.transactions_root.size() + h.receipts_root.size() + h.logs_bloom.size() + sizeof(h.difficulty) + sizeof(h.number) + sizeof(h.gas_limit) + sizeof(h.gas_used) + sizeof(h.timestamp) + h.extra_data.size() + h.mix_hash.size() + h.nonce.size() + sizeof(h.base_fee_per_gas) + sizeof(h.withdrawals_root) + sizeof(h.blob_gas_used) + sizeof(h.excess_blob_gas) + sizeof(h.parent_beacon_block_root));

    ret += h.parent_hash;
    return ret;
}

}