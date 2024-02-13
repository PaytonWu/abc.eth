// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NIBBLE_BYTES_DECL
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NIBBLE_BYTES_DECL

#pragma once

#include "nibble_bytes_fwd_decl.h"
#include "nibble_bytes_view.h"
#include "compact_bytes_view_decl.h"

#include <abc/bytes.h>
#include <abc/error.h>
#include <abc/expected.h>

#include <initializer_list>
#include <limits>
#include <vector>

namespace abc::ethereum::trie
{

class nibble_bytes
{
public:
    static constexpr std::size_t npos{nibble_bytes_view::npos};
    static constexpr char terminator{nibble_bytes_view::terminator};

private:
    using bytes_t = std::vector<byte>;

    bytes_t nibbles_;

public:
    using value_type = bytes_t::value_type;
    using size_type = bytes_t::size_type;
    using difference_type = bytes_t::difference_type;
    using reference = bytes_t::reference;
    using const_reference = bytes_t::const_reference;
    using pointer = bytes_t::pointer;
    using const_pointer = bytes_t::const_pointer;
    using iterator = bytes_t::iterator;
    using const_iterator = bytes_t::const_iterator;
    using reverse_iterator = bytes_t::reverse_iterator;
    using const_reverse_iterator = bytes_t::const_reverse_iterator;

private:
    explicit constexpr nibble_bytes(bytes_view_t bytes_view);
    explicit constexpr nibble_bytes(std::initializer_list<byte> il);
    explicit constexpr nibble_bytes(nibble_bytes_view view);

public:
    nibble_bytes() = default;

    explicit constexpr nibble_bytes(compact_bytes_view view);

    static constexpr auto
    from(bytes_view_t bytes_view) -> nibble_bytes;

    static constexpr auto
    from(std::initializer_list<byte> il) -> nibble_bytes;

    template <typename BytesT> // requires std::is_continuous_container_v<BytesT>
    auto
    to() const -> expected<BytesT, std::error_code>;

    [[nodiscard]] constexpr auto
    has_terminator() const noexcept -> bool;

    [[nodiscard]] constexpr auto
    size() const noexcept -> std::size_t;

    [[nodiscard]] constexpr auto
    empty() const noexcept -> bool;

    constexpr
    operator nibble_bytes_view() const noexcept;

    [[nodiscard]] constexpr auto
    nibbles_view(std::size_t offset, std::size_t count = npos) const -> nibble_bytes_view;

    [[nodiscard]] constexpr auto
    begin() const noexcept -> const_iterator;

    [[nodiscard]] constexpr auto
    cbegin() const noexcept -> const_iterator;

    [[nodiscard]] constexpr auto
    end() const noexcept -> const_iterator;

    [[nodiscard]] constexpr auto
    cend() const noexcept -> const_iterator;

    [[nodiscard]] constexpr auto
    operator[](std::size_t index) const -> const_reference;

    [[nodiscard]] constexpr auto
    front() const -> const_reference;

    [[nodiscard]] constexpr auto
    back() const -> const_reference;

    [[nodiscard]] constexpr auto
    first(size_t const count) const noexcept -> nibble_bytes_view;

    [[nodiscard]] constexpr auto
    last(size_t const count) const noexcept -> nibble_bytes_view;

    [[nodiscard]] friend constexpr auto
    operator==(nibble_bytes const & lhs, nibble_bytes const & rhs) noexcept -> bool = default;
};

} // namespace abc::ethereum::trie

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NIBBLE_BYTES_DECL
