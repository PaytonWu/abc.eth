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
#include <variant>

namespace abc::ethereum::trie
{

class short_node
    : public node_face
    , public clonable<short_node, std::shared_ptr<short_node>>
{
    std::optional<bytes_t> bytes_key_{};
    std::optional<compact_bytes> compact_bytes_key_{};
    std::optional<nibble_bytes> nibble_bytes_key_{};

    std::variant<bytes_t, nibble_bytes, compact_bytes> key_{};

    std::shared_ptr<node_face> value_{};
    hash_flag flag_{};

public:
    short_node() = default;
    short_node(short_node &&) = default;
    ~short_node() override = default;

    short_node(bytes_t const & raw_key, std::shared_ptr<node_face> value, hash_flag flag);
    short_node(nibble_bytes const & nibble_key, std::shared_ptr<node_face> value, hash_flag flag);
    short_node(compact_bytes const & compact_key, std::shared_ptr<node_face> value, hash_flag flag);

    auto
    operator=(short_node &&) -> short_node & = default;

private:
    short_node(short_node const &) = default;

    auto
    operator=(short_node const &) -> short_node & = default;

public:
    [[nodiscard]] auto
    clone() const -> std::shared_ptr<short_node> override;

    [[nodiscard]] auto
    cache() const -> hash_flag override;

    [[nodiscard]] auto
    fstring(std::string_view indent) const -> std::string override;

    constexpr auto
    type() const noexcept -> node_type override;

    auto
    raw_keys() const -> bytes_t const &;

    auto
    nibble_keys() const -> nibble_bytes const &;

    auto
    compact_keys() const -> compact_bytes const &;

    [[nodiscard]] constexpr auto
    value() const noexcept -> std::shared_ptr<node_face> const &;

    auto
    value(std::shared_ptr<node_face> v) -> void;
};

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_SHORT_NODE_DECL
