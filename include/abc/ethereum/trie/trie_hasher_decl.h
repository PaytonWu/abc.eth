// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIE_HASHER_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIE_HASHER_DECL

#pragma once

#include "trie_hasher_fwd_decl.h"

#include "node_face_decl.h"
#include "short_node_fwd_decl.h"
#include "full_node_fwd_decl.h"

#include <abc/bytes.h>
#include <abc/fixed_hash.h>

namespace abc::ethereum::trie
{

class trie_hasher
{
private:
    bytes_t buffer_{};
    bool parrallel_{false};

public:
    ~trie_hasher() = default;

    trie_hasher(trie_hasher &&) = default;
    trie_hasher(trie_hasher const &) = delete;

    auto
    operator=(trie_hasher &&) -> trie_hasher & = default;

    auto
    operator=(trie_hasher const &) -> trie_hasher & = delete;

    constexpr explicit trie_hasher(bool parrallel) : parrallel_{parrallel}
    {
    }

    auto
    hash(std::shared_ptr<node_face> const & node, bool force) -> std::pair<h256_t, std::shared_ptr<node_face>>;

    auto
    hash(bytes_view_t data) const -> std::shared_ptr<node_face>;

private:
    auto
    hash_short(trie::short_node * short_node, bool force) -> std::pair<std::shared_ptr<node_face>, std::shared_ptr<node_face>>;

    auto
    hash_full(trie::full_node * full_node, bool force) -> std::pair<h256_t, std::shared_ptr<node_face>>;

    auto
    short_node_hash(trie::short_node const * short_node, bool force);
};

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_TRIE_HASHER_DECL
