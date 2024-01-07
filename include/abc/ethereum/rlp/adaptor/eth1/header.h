// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ETH1_HEADER
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ETH1_HEADER

#pragma once

#include "abc/ethereum/types/eth1/header.h"
#include "abc/ethereum/rlp/concepts.h"
#include "abc/ethereum/rlp/adaptor/adaptor_base.h"

namespace abc::ethereum::rlp::adaptor
{

//template <>
//struct convert<types::eth1::header> {
//    auto
//    operator()(rlp::object const& o, T& v) const -> rlp::object const &;
//};

template <>
struct pack<types::eth1::header> {
    template <packing_stream Stream>
    auto
    operator()(packer<Stream> & o, types::eth1::header const & v) const -> packer<Stream> &
    {
        o.pack(v.parent_hash);
        o.pack(v.uncle_hash);
        o.pack(v.coinbase);
        o.pack(v.state_root);
        o.pack(v.transactions_root);
        o.pack(v.receipts_root);
        o.pack(v.logs_bloom);
        o.pack(v.difficulty);
        o.pack(v.number);
        o.pack(v.gas_limit);
        o.pack(v.gas_used);
        o.pack(v.timestamp);
        o.pack(v.extra_data);
        o.pack(v.mix_hash);
        o.pack(v.nonce);
        o.pack(v.base_fee_per_gas);
        o.pack(v.withdrawals_root);
        o.pack(v.blob_gas_used);
        o.pack(v.excess_blob_gas);
        o.pack(v.parent_beacon_block_root);
        return o;
    }
};

template <>
struct object<types::eth1::header>
{
    auto
    operator()(rlp::object& , types::eth1::header const & ) const -> void
    {

    }
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ADAPTOR_ETH1_HEADER
