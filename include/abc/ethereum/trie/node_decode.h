// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NODE_DECODE)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NODE_DECODE

#pragma once

#include "node_face.h"

#include <abc/fixed_hash.h>
#include <abc/bytes.h>
#include <abc/expected.h>

#include <memory>
#include <system_error>

namespace abc::ethereum::trie
{

auto
decode_short_node(h256_t const & hash, bytes_view_t data) -> expected<std::shared_ptr<node_face>, std::error_code>;

auto
decode_node_unsafe(h256_t const & hash, bytes_view_t data) -> expected<std::shared_ptr<node_face>, std::error_code>;

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NODE_DECODE
