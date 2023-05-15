// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETHEREUM_ERROR)
#define ABC_ETHEREUM_ERROR

#pragma once

#include <system_error>

namespace abc::ethereum {

enum class errc {
    success = 0,
    invalid_address,
    invalid_transaction,
    invalid_block,
    invalid_block_header,
    invalid_block_body,
    invalid_block_receipts,
    invalid_block_transactions,
    invalid_block_uncles,
    invalid_block_difficulty,
    invalid_block_gas_limit,
    invalid_block_gas_used,
    invalid_block_state_root,
    invalid_block_transactions_root,
    invalid_block_receipts_root,
    invalid_block_uncles_root,
    invalid_block_logs_bloom,
    invalid_block_number,
    invalid_block_timestamp,
    invalid_block_nonce,
    invalid_block_hash
};

auto make_error_code(errc ec) -> std::error_code;

auto ethereum_category() -> std::error_category const &;

}

namespace std {

template <>
struct is_error_code_enum<abc::ethereum::errc> : true_type {
};

}
#endif //ABC_ETHEREUM_ERROR
