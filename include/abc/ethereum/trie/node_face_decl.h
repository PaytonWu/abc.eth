// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NODE_FACE
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NODE_FACE

#pragma once

#include "node_face_fwd_decl.h"
#include "hash_node_decl.h"

#include <abc/ethereum/rlp/sbuffer.h>

#include <string_view>
#include <tuple>

namespace abc::ethereum::trie
{

enum class [[nodiscard]] node_type
{
    invalid,
    full,
    hash
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

    virtual auto
    cache() const -> std::tuple<hash_node, bool> = 0;

//    virtual auto
//    encode(rlp::sbuffer & buffer) const -> void = 0;

    virtual auto
    fstring(std::string_view indent) const -> std::string = 0;

    virtual auto
    type() const noexcept -> node_type = 0;
};

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NODE_FACE
