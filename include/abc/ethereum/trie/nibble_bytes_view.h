// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NIBBLE_BYTES_VIEW)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NIBBLE_BYTES_VIEW

#pragma once

#include "nibble_bytes_fwd_decl.h"
#include "nibble_bytes_view_decl.h"

#include <abc/bytes.h>

namespace abc::ethereum::trie
{

constexpr nibble_bytes_view::nibble_bytes_view(byte const * data, std::size_t size) noexcept : view_{data, size}
{
}

constexpr nibble_bytes_view::nibble_bytes_view(std::basic_string_view<byte> view) noexcept : view_{view}
{
}

template <typename BytesT> // requires std::is_continuous_container_v<BytesT>
auto
nibble_bytes_view::in_place_fill(BytesT & bytes) const -> expected<std::size_t, std::error_code>
{
    auto view_copy = view_;
    if (has_terminator())
    {
        view_copy = view_copy.substr(0, view_copy.size() - 1);
    }

    if (view_copy.size() % 2 != 0)
    {
        return make_unexpected(make_error_code(std::errc::invalid_argument));
    }

    auto const nibbles_size = view_.size();
    auto const bytes_size = nibbles_size / 2;

    if (bytes.size() < bytes_size)
    {
        return make_unexpected(make_error_code(std::errc::result_out_of_range));
    }

    for (auto i = 0u; i < bytes_size; ++i)
    {
        auto const high = view_[2 * i];
        auto const low = view_[2 * i + 1];

        assert(high < 16);
        assert(low < 16);

        bytes[i] = static_cast<abc::byte>((high << 4) | low);
    }

    return bytes_size;
}

template <typename BytesT> // requires std::is_continuous_container_v<BytesT>
auto
nibble_bytes_view::to() const -> expected<BytesT, std::error_code>
{
    auto view_copy = view_;
    if (has_terminator())
    {
        view_copy = view_copy.substr(0, view_copy.size() - 1);
    }

    if (view_copy.size() % 2 != 0)
    {
        return make_unexpected(std::make_error_code(std::errc::invalid_argument));
    }

    auto const nibbles_size = view_.size();
    auto const bytes_size = nibbles_size / 2;

    BytesT bytes{};
    bytes.reserve(bytes_size);

    for (auto i = 0u; i < bytes_size; ++i)
    {
        auto const high = view_[2 * i];
        auto const low = view_[2 * i + 1];

        assert(high < 16);
        assert(low < 16);

        auto const byte = static_cast<abc::byte>((high << 4) | low);

        bytes.push_back(byte);
    }

    return bytes;
}

constexpr auto
nibble_bytes_view::has_terminator() const noexcept -> bool
{
    return !view_.empty() && view_.back() == terminator;
}

constexpr auto
nibble_bytes_view::begin() const noexcept -> const_iterator
{
    return view_.begin();
}

constexpr auto
nibble_bytes_view::cbegin() const noexcept -> const_iterator
{
    return view_.cbegin();
}

constexpr auto
nibble_bytes_view::end() const noexcept -> const_iterator
{
    return view_.end();
}

constexpr auto
nibble_bytes_view::cend() const noexcept -> const_iterator
{
    return view_.cend();
}

constexpr auto
nibble_bytes_view::rbegin() const noexcept -> const_reverse_iterator
{
    return view_.rbegin();
}

constexpr auto
nibble_bytes_view::crbegin() const noexcept -> const_reverse_iterator
{
    return view_.crbegin();
}

constexpr auto
nibble_bytes_view::rend() const noexcept -> const_reverse_iterator
{
    return view_.rend();
}

constexpr auto
nibble_bytes_view::crend() const noexcept -> const_reverse_iterator
{
    return view_.crend();
}

constexpr auto
nibble_bytes_view::front() const -> const_reference
{
    return view_.front();
}

constexpr auto
nibble_bytes_view::back() const -> const_reference
{
    return view_.back();
}

constexpr auto
nibble_bytes_view::operator[](size_type idx) const -> const_reference
{
    return view_[idx];
}

constexpr auto
nibble_bytes_view::at(size_type pos) const -> const_reference
{
    return view_.at(pos);
}

constexpr auto
nibble_bytes_view::data() const noexcept -> const_pointer
{
    return view_.data();
}

constexpr auto
nibble_bytes_view::size() const noexcept -> size_type
{
    return view_.size();
}

constexpr auto
nibble_bytes_view::empty() const noexcept -> bool
{
    return view_.empty();
}

template <std::size_t Count>
constexpr auto
nibble_bytes_view::first() const -> nibble_bytes_view
{
    return nibble_bytes_view{view_.substr(0, Count)};
}

constexpr auto
nibble_bytes_view::first(size_type count) const -> nibble_bytes_view
{
    return nibble_bytes_view{view_.substr(0, count)};
}

template <std::size_t Count>
constexpr auto
nibble_bytes_view::last() const -> nibble_bytes_view
{
    return nibble_bytes_view{view_.substr(view_.size() - Count)};
}

constexpr auto
nibble_bytes_view::last(size_type count) const -> nibble_bytes_view
{
    return nibble_bytes_view{view_.substr(view_.size() - count)};
}

constexpr auto
nibble_bytes_view::subview(size_type offset, size_type count) const -> nibble_bytes_view
{
    return {view_.substr(offset, count)};
}

constexpr auto
common_prefix_length(nibble_bytes_view lhs, nibble_bytes_view rhs) noexcept -> std::size_t
{
    auto const min_size = std::min(lhs.size(), rhs.size());
    auto i = 0u;
    for (; i < min_size; ++i)
    {
        if (lhs[i] != rhs[i])
        {
            break;
        }
    }

    return i;
}

} // namespace abc::ethereum::trie

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NIBBLE_BYTES_VIEW
