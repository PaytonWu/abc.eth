// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NIBBLE_BYTES_VIEW)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NIBBLE_BYTES_VIEW

#pragma once

#include "nibble_bytes_fwd_decl.h"
#include "nibble_bytes_view_fwd_decl.h"

#include <abc/byte.h>

#include <span>
#include <string_view>

namespace abc::ethereum::trie
{

class nibble_bytes_view
{
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
    constexpr nibble_bytes_view(byte const * data, std::size_t size) noexcept : view_{data, size}
    {
    }

    constexpr nibble_bytes_view(std::basic_string_view<byte> view) noexcept : view_{view}
    {
    }

public:
    constexpr nibble_bytes_view() = default;

    nibble_bytes_view(std::nullptr_t) = delete;

    [[nodiscard]] constexpr auto
    begin() const noexcept -> const_iterator
    {
        return view_.begin();
    }

    [[nodiscard]] constexpr auto
    cbegin() const noexcept -> const_iterator
    {
        return view_.cbegin();
    }

    [[nodiscard]] constexpr auto
    end() const noexcept -> const_iterator
    {
        return view_.end();
    }

    [[nodiscard]] constexpr auto
    cend() const noexcept -> const_iterator
    {
        return view_.cend();
    }

    [[nodiscard]] constexpr auto
    rbegin() const noexcept -> const_reverse_iterator
    {
        return view_.rbegin();
    }

    [[nodiscard]] constexpr auto
    crbegin() const noexcept -> const_reverse_iterator
    {
        return view_.crbegin();
    }

    [[nodiscard]] constexpr auto
    rend() const noexcept -> const_reverse_iterator
    {
        return view_.rend();
    }

    [[nodiscard]] constexpr auto
    crend() const noexcept -> const_reverse_iterator
    {
        return view_.crend();
    }

    [[nodiscard]] constexpr auto
    front() const -> const_reference
    {
        return view_.front();
    }

    [[nodiscard]] constexpr auto
    back() const -> const_reference
    {
        return view_.back();
    }

    [[nodiscard]] constexpr auto
    operator[](size_type idx) const -> const_reference
    {
        return view_[idx];
    }

    [[nodiscard]] constexpr auto
    at(size_type pos) const -> const_reference
    {
        return view_.at(pos);
    }

    [[nodiscard]] constexpr auto
    data() const noexcept -> const_pointer
    {
        return view_.data();
    }

    [[nodiscard]] constexpr auto
    size() const noexcept -> size_type
    {
        return view_.size();
    }

    [[nodiscard]] constexpr auto
    empty() const noexcept -> bool
    {
        return view_.empty();
    }

    template <std::size_t Count>
    constexpr auto
    first() const -> nibble_bytes_view
    {
        return nibble_bytes_view{view_.substr(0, Count)};
    }

    constexpr auto
    first(size_type count) const -> nibble_bytes_view
    {
        return nibble_bytes_view{view_.substr(0, count)};
    }

    template <std::size_t Count>
    constexpr auto
    last() const -> nibble_bytes_view
    {
        return nibble_bytes_view{view_.substr(view_.size() - Count)};
    }

    constexpr auto
    last(size_type count) const -> nibble_bytes_view
    {
        return nibble_bytes_view{view_.substr(view_.size() - count)};
    }

    template <std::size_t Offset, std::size_t Count = std::dynamic_extent>
    constexpr auto
    subview() const -> nibble_bytes_view
    {
        return {view_.substr(Offset, Count)};
    }

    constexpr auto
    subview(size_type offset, size_type count = std::dynamic_extent) const -> nibble_bytes_view
    {
        return {view_.substr(offset, count)};
    }
};

} // namespace abc::ethereum::trie

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NIBBLE_BYTES_VIEW
