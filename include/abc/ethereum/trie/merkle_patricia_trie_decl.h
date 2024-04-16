// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_MERKLE_PATRICIA_TRIE_DECL
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_MERKLE_PATRICIA_TRIE_DECL

#pragma once

#include "merkle_patricia_trie_fwd_decl.h"
#include "node_face_decl.h"
#include "nibble_bytes_view_decl.h"
#include "hash_node_fwd_decl.h"
#include "trie_reader_decl.h"

#include <abc/bytes.h>
#include <abc/expected.h>
#include <abc/fixed_hash.h>

#include <system_error>
#include <memory>

namespace abc::ethereum::trie
{

struct update_result
{
    std::shared_ptr<node_face> node{nullptr};
    bool dirty{false};
};

// template <typename DbReaderT>
class merkle_patricia_trie
{
private:
    std::unique_ptr<trie_reader> db_reader_{nullptr};
    bool committed_{false};
    std::shared_ptr<node_face> root_{nullptr};

public:
    merkle_patricia_trie(merkle_patricia_trie const &) = delete;
    merkle_patricia_trie(merkle_patricia_trie &&) = default;

    auto
    operator=(merkle_patricia_trie const &) -> merkle_patricia_trie & = delete;

    auto
    operator=(merkle_patricia_trie &&) -> merkle_patricia_trie & = default;

    ~merkle_patricia_trie() = default;

    constexpr explicit
    merkle_patricia_trie(std::unique_ptr<trie_reader> db_reader);

public:
    auto
    hash() const -> h256_t;

    auto
    get(bytes_view_t key) const -> expected<bytes_t, std::error_code>;

    auto
    update(bytes_view_t key, bytes_view_t value) -> expected<void, std::error_code>;

private:
    auto
    try_get(bytes_view_t key) const -> expected<bytes_t, std::error_code>;

    auto
    try_update(bytes_view_t key, bytes_view_t value, std::error_code & ec) -> void;

    auto
    insert(std::shared_ptr<node_face> const & node, nibble_bytes_view prefix, nibble_bytes_view key, std::shared_ptr<node_face> const & value) -> expected<update_result, std::error_code>;

    auto
    remove(std::shared_ptr<node_face> const & node, nibble_bytes_view prefix, nibble_bytes_view key) -> expected<update_result, std::error_code>;

    auto
    resolve(trie::hash_node * hash_node, nibble_bytes_view prefix) -> expected<std::shared_ptr<node_face>, std::error_code>;
};

} // namespace abc::ethereum::trie

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_MERKLE_PATRICIA_TRIE_DECL
