// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_FULL_NODE_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_FULL_NODE_DECL

#pragma once

#include "full_node_fwd_decl.h"

#include "hash_flag_decl.h"
#include "node_face_decl.h"

#include <abc/clonable.h>
#include <abc/memory.h>

#include <array>
#include <memory>

namespace abc::ethereum::trie
{

class full_node
    : public node_face
    , public clonable<full_node, std::shared_ptr<full_node>>
{
public:
    static constexpr std::size_t children_size = 17;

private:
    std::array<std::shared_ptr<node_face>, children_size> children_{};
    hash_flag flag_{};

public:
    full_node() = default;

    full_node(full_node &&) = default;
    ~full_node() override = default;

    explicit full_node(h256_t const & hash);

    auto
    operator=(full_node &&) -> full_node & = default;

private:
    full_node(full_node const &) = default;

    auto
    operator=(full_node const &) -> full_node & = default;

public:
    [[nodiscard]] auto
    clone() const -> std::shared_ptr<full_node> override;

    [[nodiscard]] auto
    cache() const -> hash_flag override;

    [[nodiscard]] auto
    fstring(std::string_view indent) const -> std::string override;

    constexpr auto
    type() const noexcept -> node_type override;

    [[nodiscard]] auto
    children(std::size_t index) const noexcept -> observer_ptr<node_face>;

    [[nodiscard]] auto
    children(std::size_t index) noexcept -> std::shared_ptr<node_face> &;
};

} // namespace abc::ethereum::trie

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_FULL_NODE_DECL
