// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ERROR
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ERROR

#pragma once

#include <system_error>
#include <type_traits>

namespace abc::ethereum::rlp
{

enum class errc
{
    success,
    empty_input,
    invalid_encoded_data,
    stack_overflow,
    unpack_error,
    type_error,
    unexpected_eof,
    expected_bytes,
    expected_list,
    non_canonical_integral,
    non_canonical_size,
    uint_overflow,
    value_too_large,
};

auto
make_error_code(errc ec) -> std::error_code;

auto
ethereum_rlp_category() -> std::error_category const &;

} // namespace abc::ethereum::rlp

namespace std
{

template <>
struct is_error_code_enum<abc::ethereum::rlp::errc> : true_type
{
};

} // namespace std

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ERROR
