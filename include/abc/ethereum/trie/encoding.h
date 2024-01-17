// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_ENCODING
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_ENCODING

#pragma once

#include <abc/bytes.h>
#include <abc/expected.h>

#include <system_error>

namespace abc::ethereum::trie
{

auto
key_bytes_to_hex(bytes_view_t key) -> bytes_t;

auto
hex_to_key_bytes(bytes_view_t hex) -> expected<bytes_t, std::error_code>;

auto
decode_nibbles(bytes_view_t nibbles) -> bytes_t;

auto
has_terminator(bytes_view_t nibbles) -> bool;

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_ENCODING
