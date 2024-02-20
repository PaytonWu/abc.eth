// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/types/rlp/eth1/header.h>

#include <abc/ethereum/rlp/error.h>

namespace abc::ethereum::rlp::adaptor
{

auto
as<types::eth1::header>::operator()(rlp::object const & o) const -> types::eth1::header
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

auto
convert<types::eth1::header>::operator()(rlp::object const & o, types::eth1::header & v) const -> rlp::object const &
{
    v = as<types::eth1::header>{}(o);
    return o;
}

auto
object<types::eth1::header>::operator()(rlp::object &, types::eth1::header const &) const -> void
{
}

} // namespace abc::ethereum::rlp::adaptor
