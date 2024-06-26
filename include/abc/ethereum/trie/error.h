// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_ERROR
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_ERROR

#pragma once

#include <system_error>

namespace abc::ethereum::trie
{

enum class errc
{
    success,
    trie_already_committed,
    unexpected_eof,
    missing_node,
    over_sized_embedded_node,
    invalid_number_of_list_elements,
};

auto
make_error_code(errc ec) -> std::error_code;

auto
ethereum_trie_category() -> std::error_category const &;

} // namespace abc::ethereum::trie

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_ERROR
