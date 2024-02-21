// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_FULL_NODE_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_FULL_NODE_DECL

#pragma once

#include "full_node_fwd_decl.h"
#include "node_face_fwd_decl.h"
#include "node_flag_decl.h"
// #include "node_variant_decl.h"

#include <abc/memory.h>

#include <array>
#include <memory>

namespace abc::ethereum::trie
{

class full_node : public node_face
{
public:
    static constexpr std::size_t children_size = 17;
private:
    std::array<std::shared_ptr<node_face>, children_size> children_{};
    std::array<std::unique_ptr<node_face>, children_size> children2_{};
    node_flag flag_{};

public:
    full_node() = default;

    full_node(full_node const &) = delete;
    full_node(full_node &&) = default;

    auto
    operator=(full_node const &) -> full_node & = delete;

    auto
    operator=(full_node &&) -> full_node & = default;

public:
    [[nodiscard]] auto
    cache() const -> std::tuple<hash_node, bool> override;

    [[nodiscard]] auto
    fstring(std::string_view indent) const -> std::string override;

    constexpr auto
    type() const noexcept -> node_type override;

    [[nodiscard]] auto
    children(std::size_t index) const noexcept -> observer_ptr<node_face>;

    [[nodiscard]] auto
    children(std::size_t index) noexcept -> std::shared_ptr<node_face> &;

    [[nodiscard]] auto
    clone() const -> std::unique_ptr<node_face>;
};

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_FULL_NODE_DECL
