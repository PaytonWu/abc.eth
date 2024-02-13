// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_ENCODING
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_ENCODING

#pragma once

#include "nibble_bytes.h"

#include <abc/bytes.h>
#include <abc/expected.h>

#include <system_error>

namespace abc::ethereum::trie
{

constexpr auto
key_bytes_to_nibble_bytes(bytes_view_t key) -> nibble_bytes
{
    return nibble_bytes::from(key);
}

auto
nibble_bytes_to_key_bytes(nibble_bytes_view nibble_bytes_view) -> expected<abc::bytes_t, std::error_code>;

} // namespace abc::ethereum::trie

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_ENCODING
