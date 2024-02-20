// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_RLP_ETH1_HEADER)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_RLP_ETH1_HEADER

#pragma once

#include "header_decl.h"

#include <abc/ethereum/types/eth1/header.h>

#include <abc/ethereum/rlp/adaptor/abc/bytes.h>
#include <abc/ethereum/rlp/adaptor/abc/fixed_bytes.h>
#include <abc/ethereum/rlp/adaptor/abc/uint128.h>
#include <abc/ethereum/rlp/adaptor/adaptor_base.h>
#include <abc/ethereum/rlp/adaptor/unsigned_integral.h>
#include <abc/ethereum/rlp/concepts.h>

namespace abc::ethereum::rlp::adaptor
{

template <packing_stream Stream>
auto
pack<types::eth1::header>::operator()(packer<Stream> & o, types::eth1::header const & v) const -> packer<Stream> &
{
    o.pack_bytes(v.parent_hash);
    o.pack_bytes(v.uncle_hash);
    o.pack_bytes(v.coinbase.bytes());
    o.pack_bytes(v.state_root);
    o.pack_bytes(v.transactions_root);
    o.pack_bytes(v.receipts_root);
    o.pack_bytes(v.logs_bloom);
    o.pack_uint128(v.difficulty);
    o.pack_unsigned_integral(v.number);
    o.pack_unsigned_integral(v.gas_limit);
    o.pack_unsigned_integral(v.gas_used);
    o.pack_unsigned_integral(v.timestamp);
    o.pack_bytes(v.extra_data);
    o.pack_bytes(v.mix_hash);
    o.pack_bytes(v.nonce);
    o.pack_optional(v.base_fee_per_gas);
    o.pack_optional(v.withdrawals_root);
    o.pack_optional(v.blob_gas_used);
    o.pack_optional(v.excess_blob_gas);
    o.pack_optional(v.parent_beacon_block_root);
    return o;
}

} // namespace abc::ethereum::rlp::adaptor

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_RLP_ETH1_HEADER
