// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NIBBLE_BYTES_VIEW_DECL
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NIBBLE_BYTES_VIEW_DECL

#pragma once

#include "nibble_bytes_fwd_decl.h"
#include "nibble_bytes_view_fwd_decl.h"

#include <abc/byte.h>
#include <abc/expected.h>

#include <limits>
#include <string_view>
#include <system_error>

namespace abc::ethereum::trie
{

class nibble_bytes_view
{
public:
    static constexpr std::size_t npos{std::numeric_limits<std::size_t>::max()};
    static constexpr char terminator{static_cast<char>(0x10)};

private:
    using container_type = std::basic_string_view<byte>;
    container_type view_{};

    friend class nibble_bytes;

public:
    using value_type = typename container_type::value_type;
    using size_type = typename container_type::size_type;
    using difference_type = typename container_type::difference_type;
    using pointer = typename container_type::pointer;
    using const_pointer = typename container_type::const_pointer;
    using reference = typename container_type::reference;
    using const_reference = typename container_type::const_reference;
    using iterator = typename container_type::const_iterator;
    using const_iterator = typename container_type::const_iterator;
    using reverse_iterator = typename container_type::const_reverse_iterator;
    using const_reverse_iterator = typename container_type::const_reverse_iterator;

private:
    constexpr nibble_bytes_view(byte const * data, std::size_t size) noexcept;

    constexpr nibble_bytes_view(std::basic_string_view<byte> view) noexcept;

public:
    constexpr nibble_bytes_view() = default;

    nibble_bytes_view(std::nullptr_t) = delete;

    [[nodiscard]] friend constexpr auto
    operator==(nibble_bytes_view lhs, nibble_bytes_view rhs) noexcept -> bool = default;

    template <typename BytesT> // requires std::is_continuous_container_v<BytesT>
    auto
    in_place_fill(BytesT & bytes) const -> expected<std::size_t, std::error_code>;

    template <typename BytesT> // requires std::is_continuous_container_v<BytesT>
    auto
    to() const -> expected<BytesT, std::error_code>;

    [[nodiscard]] constexpr auto
    has_terminator() const noexcept -> bool;

    [[nodiscard]] constexpr auto
    begin() const noexcept -> const_iterator;

    [[nodiscard]] constexpr auto
    cbegin() const noexcept -> const_iterator;

    [[nodiscard]] constexpr auto
    end() const noexcept -> const_iterator;

    [[nodiscard]] constexpr auto
    cend() const noexcept -> const_iterator;

    [[nodiscard]] constexpr auto
    rbegin() const noexcept -> const_reverse_iterator;

    [[nodiscard]] constexpr auto
    crbegin() const noexcept -> const_reverse_iterator;

    [[nodiscard]] constexpr auto
    rend() const noexcept -> const_reverse_iterator;

    [[nodiscard]] constexpr auto
    crend() const noexcept -> const_reverse_iterator;

    [[nodiscard]] constexpr auto
    front() const -> const_reference;

    [[nodiscard]] constexpr auto
    back() const -> const_reference;

    [[nodiscard]] constexpr auto
    operator[](size_type idx) const -> const_reference;

    [[nodiscard]] constexpr auto
    at(size_type pos) const -> const_reference;

    [[nodiscard]] constexpr auto
    data() const noexcept -> const_pointer;

    [[nodiscard]] constexpr auto
    size() const noexcept -> size_type;

    [[nodiscard]] constexpr auto
    empty() const noexcept -> bool;

    template <std::size_t Count>
    constexpr auto
    first() const -> nibble_bytes_view;

    constexpr auto
    first(size_type count) const -> nibble_bytes_view;

    template <std::size_t Count>
    constexpr auto
    last() const -> nibble_bytes_view;

    constexpr auto
    last(size_type count) const -> nibble_bytes_view;

    constexpr auto
    subview(size_type offset, size_type count = npos) const -> nibble_bytes_view;
};

[[nodiscard]] constexpr auto
common_prefix_length(nibble_bytes_view lhs, nibble_bytes_view rhs) noexcept -> std::size_t;

} // namespace abc::ethereum::trie

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NIBBLE_BYTES_VIEW_DECL
