// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ERROR
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ERROR

#pragma once

#include <system_error>
#include <type_traits>

namespace abc::ethereum::rlp {

enum class errc {
    success,
    empty_input,
    invalid_encoded_data,
    stack_overflow,
};

auto make_error_code(errc ec) -> std::error_code;

auto rlp_category() -> std::error_category const &;

}

namespace std {

template <>
struct is_error_code_enum<abc::ethereum::rlp::errc> : true_type {
};


}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ERROR
