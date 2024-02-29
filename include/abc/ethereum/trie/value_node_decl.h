// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_VALUE_NODE_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_VALUE_NODE_DECL

#pragma once

#include "value_node_decl.h"

#include "node_face_decl.h"

#include <abc/bytes.h>

namespace abc::ethereum::trie
{

class value_node : public node_face
{
private:
    bytes_t value_;

public:
    value_node() = default;
    value_node(value_node const &) = default;
    value_node(value_node &&) = default;
    ~value_node() override = default;

    auto operator=(value_node const &) -> value_node & = default;
    auto operator=(value_node &&) -> value_node & = default;

    [[nodiscard]] constexpr auto
    cache() const -> hash_flag override;

    [[nodiscard]] auto
    fstring(std::string_view indent) const -> std::string override;

    constexpr auto
    type() const noexcept -> node_type override;

    constexpr auto
    value() const noexcept -> bytes_view_t;
};

}


#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_VALUE_NODE_DECL
