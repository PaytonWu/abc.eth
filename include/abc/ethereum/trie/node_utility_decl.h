// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NODE_UTILITY_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NODE_UTILITY_DECL

#pragma once

#include "node_face_decl.h"

#include <abc/expected.h>
#include <abc/fixed_hash.h>

#include <memory>
#include <system_error>

namespace abc::ethereum::trie
{

[[nodiscard]] auto
must_decode_node(h256_t const & hash, bytes_view_t buf) -> std::shared_ptr<node_face>;

auto
decode_node(h256_t const & hash, bytes_view_t buf) -> expected<std::shared_ptr<node_face>, std::error_code>;

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NODE_UTILITY_DECL
