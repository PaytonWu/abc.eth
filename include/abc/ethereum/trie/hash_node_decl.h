// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_HASH_NODE_DECL
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_HASH_NODE_DECL

#pragma once

#include "hash_node_fwd_decl.h"
#include "node_face_decl.h"

#include <abc/fixed_hash.h>

namespace abc::ethereum::trie
{

class hash_node : public node_face
{
private:
    h256_t hash_{};

public:
    hash_node() = default;
    hash_node(hash_node const &) = default;
    hash_node(hash_node &&) = default;
    ~hash_node() override = default;

    constexpr hash_node(h256_t const & hash);

    constexpr auto
    operator=(hash_node const &) -> hash_node & = default;

    constexpr auto
    operator=(hash_node &&) -> hash_node & = default;

    [[nodiscard]] constexpr auto
    cache() const -> hash_flag override;

//    auto
//    encode(rlp::sbuffer & buffer) const -> void override;

    [[nodiscard]] auto
    fstring(std::string_view indent) const -> std::string override;

    constexpr auto
    type() const noexcept -> node_type override;

    constexpr auto
    hash() const noexcept -> h256_t const &;
};

} // namespace abc::ethereum::trie

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_HASH_NODE_DECL
