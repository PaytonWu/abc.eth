// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_COMPACT_BYTES_VIEW_DECL
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_COMPACT_BYTES_VIEW_DECL

#pragma once

#include "compact_bytes_fwd_decl.h"
#include "compact_bytes_view_fwd_decl.h"

#include <abc/byte.h>

#include <string_view>

namespace abc::ethereum::trie
{

class compact_bytes_view
{
private:
    friend class compact_bytes;

    using view_t = std::basic_string_view<abc::byte>;
    view_t view_{};

public:
    using value_type = view_t::value_type;
    using size_type = view_t::size_type;
    using difference_type = view_t::difference_type;
    using pointer = view_t::pointer;
    using const_pointer = view_t::const_pointer;
    using reference = view_t::reference;
    using const_reference = view_t::const_reference;
    using iterator = view_t::const_iterator;
    using const_iterator = view_t::const_iterator;
    using reverse_iterator = view_t::const_reverse_iterator;
    using const_reverse_iterator = view_t::const_reverse_iterator;

private:
    constexpr compact_bytes_view(abc::byte const * data, std::size_t size) noexcept;

public:
    constexpr compact_bytes_view() = default;

    compact_bytes_view(std::nullptr_t) = delete;

    [[nodiscard]] constexpr auto
    size() const noexcept -> size_type;

    [[nodiscard]] constexpr auto
    empty() const noexcept -> bool;

    [[nodiscard]] constexpr auto
    data() const noexcept -> const_pointer;

    [[nodiscard]] constexpr auto
    begin() const noexcept -> const_iterator;

    [[nodiscard]] constexpr auto
    end() const noexcept -> const_iterator;

    [[nodiscard]] constexpr auto
    operator[](size_type pos) const noexcept -> const_reference;

    [[nodiscard]] constexpr auto
    at(size_type pos) const -> const_reference;

    [[nodiscard]] constexpr auto
    front() const noexcept -> const_reference;

    [[nodiscard]] constexpr auto
    back() const noexcept -> const_reference;
};

} // namespace abc::ethereum::trie

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_COMPACT_BYTES_VIEW_DECL
