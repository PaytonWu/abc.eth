// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_RLP_NODE_DECODE)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_RLP_NODE_DECODE

#pragma once

#include <abc/ethereum/trie/full_node.h>
#include <abc/ethereum/trie/node_face.h>
#include <abc/ethereum/trie/short_node.h>

#include <abc/bytes.h>
#include <abc/expected.h>
#include <abc/fixed_hash.h>

#include <memory>
#include <system_error>
#include <utility>

namespace abc::ethereum::trie::rlp
{

auto
decode_ref(bytes_view_t buf) -> expected<std::pair<std::shared_ptr<node_face>, bytes_view_t>, std::error_code>;

auto
decode_short_node(h256_t const & hash, bytes_view_t data) -> expected<std::shared_ptr<short_node>, std::error_code>;

auto
decode_full_node(h256_t const & hash, bytes_view_t data) -> expected<std::shared_ptr<full_node>, std::error_code>;

auto
decode_node_unsafe(h256_t const & hash, bytes_view_t data) -> expected<std::shared_ptr<node_face>, std::error_code>;

auto
must_decode_node_unsafe(h256_t const & hash, bytes_view_t data) -> std::shared_ptr<node_face>;

auto
decode_node(h256_t const & hash, bytes_view_t data) -> expected<std::shared_ptr<node_face>, std::error_code>;

auto
must_decode_node(h256_t const & hash, bytes_view_t data) -> std::shared_ptr<node_face>;

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_RLP_NODE_DECODE
