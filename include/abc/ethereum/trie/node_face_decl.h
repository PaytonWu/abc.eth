// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NODE_FACE)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NODE_FACE

#pragma once

#include "node_face_fwd_decl.h"

#include "hash_flag_decl.h"

#include <string_view>

namespace abc::ethereum::trie
{

enum class [[nodiscard]] node_type
{
    invalid,
    full_node,
    hash_node,
    short_node,
    value_node,
};

class [[nodiscard]] node_face
{
public:
    node_face() = default;
    node_face(node_face const &) = default;
    node_face(node_face &&) = default;
    virtual ~node_face() = default;

    auto operator=(node_face const &) -> node_face & = default;
    auto operator=(node_face &&) -> node_face & = default;

    [[nodiscard]] virtual auto
    cache() const -> hash_flag = 0;

    [[nodiscard]] virtual auto
    fstring(std::string_view indent) const -> std::string = 0;

    virtual auto
    type() const noexcept -> node_type = 0;
};

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NODE_FACE
