// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_CRYPTO_ERROR
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_CRYPTO_ERROR

#pragma once

#include <system_error>

namespace abc::ethereum::crypto
{

enum class errc
{
    success = 0,
    invalid_private_key,
    invalid_private_key_length,
    invalid_public_key,
};

auto
make_error_code(errc ec) -> std::error_code;

auto
ethereum_crypto_category() -> std::error_category const &;

} // namespace abc::ethereum::crypto

namespace std
{

template <>
struct is_error_code_enum<abc::ethereum::crypto::errc> : true_type
{
};

} // namespace std

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_CRYPTO_ERROR
