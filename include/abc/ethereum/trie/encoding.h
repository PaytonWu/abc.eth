// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_ENCODING
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_ENCODING

#pragma once

#include <abc/hex_string.h>
#include <abc/bytes_view.h>

namespace abc::ethereum::trie
{

auto key_bytes_to_hex(bytes_view_t key) -> hex_string;

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_ENCODING
