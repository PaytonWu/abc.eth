// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_MERKLE_PATRICIA_TRIE_DECL
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_MERKLE_PATRICIA_TRIE_DECL

#pragma once

#include <abc/bytes.h>
#include <abc/expected.h>
#include <abc/fixed_hash.h>

#include <system_error>

namespace abc::ethereum::trie
{

template <typename TrieDbT>
class merkle_patricia_trie
{
private:
    TrieDbT * db_{ nullptr };
    bool committed_{ false };

public:
    merkle_patricia_trie(merkle_patricia_trie const &) = delete;
    merkle_patricia_trie(merkle_patricia_trie &&) = default;
    auto operator=(merkle_patricia_trie const &) -> merkle_patricia_trie & = delete;
    auto operator=(merkle_patricia_trie &&) -> merkle_patricia_trie & = default;
    ~merkle_patricia_trie() = default;

    explicit merkle_patricia_trie(TrieDbT * db);

public:
    auto hash() const -> h256_t;
    auto get(bytes_view_t key) const -> expected<bytes_t, std::error_code>;
    auto update(bytes_view_t key, bytes_view_t value, std::error_code & ec) -> void;

private:
    auto try_get(bytes_view_t key) const -> expected<bytes_t, std::error_code>;
    auto try_update(bytes_view_t key, bytes_view_t value, std::error_code & ec) -> void;

    auto insert(bytes_view_t key, bytes_view_t value, std::error_code & ec) -> void;
    auto remove(bytes_view_t key, std::error_code & ec) -> void;
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_MERKLE_PATRICIA_TRIE_DECL
