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
    h256_t parent_hash{};
    h256_t uncle_hash{};
    address coinbase{};
    h256_t state_root{};
    h256_t transactions_root{};
    h256_t receipts_root{};
    bytes256_t logs_bloom{};
    uint128_t difficulty{};
    uint64_t number{};
    uint64_t gas_limit{};
    uint64_t gas_used{};
    uint64_t timestamp{};
    bytes_t extra_data{};
    h256_t mix_hash{};
    bytes8_be_t nonce{};

    std::optional<uint128_t> base_fee_per_gas{};
    std::optional<h256_t> withdrawals_root{};
    std::optional<uint64_t> blob_gas_used{};
    std::optional<uint64_t> excess_blob_gas{};
    std::optional<h256_t> parent_beacon_block_root{};

    friend
    auto
    operator==(header const & lhs, header const & rhs) noexcept -> bool = default;
};

}

#include <abc/ethereum/rlp/adaptor/abc/bytes.h>
#include <abc/ethereum/rlp/adaptor/abc/fixed_bytes.h>
#include <abc/ethereum/rlp/adaptor/abc/uint128.h>
#include <abc/ethereum/rlp/adaptor/adaptor_base.h>
#include <abc/ethereum/rlp/adaptor/as_fwd_decl.h>
#include <abc/ethereum/rlp/adaptor/unsigned_integral.h>
#include <abc/ethereum/rlp/concepts.h>
#include <abc/ethereum/rlp/error.h>

namespace abc::ethereum::rlp::adaptor
{

template <>
struct as<types::eth1::header>
{
    auto
    operator()(rlp::object const & o) const -> types::eth1::header
    {
        if (o.type != rlp::type::list || o.data.array.size < 15)
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::type_error));
        }

        types::eth1::header r;
        switch (o.data.array.size - 1)
        {
            default:
                [[fallthrough]];

            case 19:
                r.parent_beacon_block_root = o.data.array.ptr[19].as<h256_t>();
                [[fallthrough]];

            case 18:
                r.excess_blob_gas = o.data.array.ptr[18].as<uint64_t>();
                [[fallthrough]];

            case 17:
                r.blob_gas_used = o.data.array.ptr[17].as<uint64_t>();
                [[fallthrough]];

            case 16:
                r.withdrawals_root = o.data.array.ptr[16].as<h256_t>();
                [[fallthrough]];

            case 15:
                r.base_fee_per_gas = o.data.array.ptr[15].as<uint128_t>();
                [[fallthrough]];

            case 14:
                r.nonce = o.data.array.ptr[14].as<bytes8_be_t>();
                r.mix_hash = o.data.array.ptr[13].as<h256_t>();
                r.extra_data = o.data.array.ptr[12].as<bytes_t>();
                r.timestamp = o.data.array.ptr[11].as<uint64_t>();
                r.gas_used = o.data.array.ptr[10].as<uint64_t>();
                r.gas_limit = o.data.array.ptr[9].as<uint64_t>();
                r.number = o.data.array.ptr[8].as<uint64_t>();
                r.difficulty = o.data.array.ptr[7].as<uint128_t>();
                r.logs_bloom = o.data.array.ptr[6].as<bytes256_t>();
                r.receipts_root = o.data.array.ptr[5].as<h256_t>();
                r.transactions_root = o.data.array.ptr[4].as<h256_t>();
                r.state_root = o.data.array.ptr[3].as<h256_t>();
                r.coinbase = o.data.array.ptr[2].as<types::address>();
                r.uncle_hash = o.data.array.ptr[1].as<h256_t>();
                r.parent_hash = o.data.array.ptr[0].as<h256_t>();
                break;
        }

        return r;
    }
};

template <>
struct convert<types::eth1::header>
{
    auto
    operator()(rlp::object const & o, types::eth1::header & v) const -> rlp::object const &
    {
        v = as<types::eth1::header>{}(o);
        return o;
    }
};

template <>
struct pack<types::eth1::header> {
    template <packing_stream Stream>
    auto
    operator()(packer<Stream> & o, types::eth1::header const & v) const -> packer<Stream> &
    {
        o.pack_bytes(v.parent_hash);
        o.pack_bytes(v.uncle_hash);
        o.pack_bytes(v.coinbase.bytes());
        o.pack_bytes(v.state_root);
        o.pack_bytes(v.transactions_root);
        o.pack_bytes(v.receipts_root);
        o.pack_bytes(v.logs_bloom);
        o.pack_uint128(v.difficulty);
        o.pack(v.number);
        o.pack(v.gas_limit);
        o.pack(v.gas_used);
        o.pack(v.timestamp);
        o.pack_bytes(v.extra_data);
        o.pack_bytes(v.mix_hash);
        o.pack_bytes(v.nonce);
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

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_ETH1_HEADER
