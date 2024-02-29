// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_SHORT_NODE_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_SHORT_NODE_DECL

#pragma once

#include "short_node_fwd_decl.h"

#include "compact_bytes_decl.h"
#include "hash_flag_decl.h"
#include "nibble_bytes_decl.h"
#include "node_face_decl.h"

#include <abc/bytes.h>

#include <memory>
#include <optional>

namespace abc::ethereum::trie
{

class short_node : public node_face
{
    std::optional<bytes_t> bytes_key_{};
    std::optional<compact_bytes> compact_bytes_key_{};
    std::optional<nibble_bytes> nibble_bytes_key_{};

    std::unique_ptr<node_face> value_{};
    hash_flag flag_{};

public:
    short_node() = default;
    short_node(short_node const &) = delete;
    short_node(short_node &&) = default;
    ~short_node() override = default;

    auto
    operator=(short_node const &) -> short_node & = delete;

    auto
    operator=(short_node &&) -> short_node & = default;

public:
    [[nodiscard]] auto
    cache() const -> hash_flag override;

    [[nodiscard]] auto
    fstring(std::string_view indent) const -> std::string override;

    constexpr auto
    type() const noexcept -> node_type override;
};

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_SHORT_NODE_DECL
