// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETHEREUM_ERROR)
#define ABC_ETHEREUM_ERROR

#pragma once

#include <system_error>

namespace abc::ethereum::types
{

enum class errc
{
    success = 0,
    invalid_address,
};

auto
make_error_code(errc ec) -> std::error_code;

auto
ethereum_category() -> std::error_category const &;

} // namespace abc::ethereum::types

namespace std
{

template <>
struct is_error_code_enum<abc::ethereum::types::errc> : true_type
{
};

} // namespace std
#endif // ABC_ETHEREUM_ERROR
