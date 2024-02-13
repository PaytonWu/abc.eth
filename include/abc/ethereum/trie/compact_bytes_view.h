// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_COMPACT_BYTES_VIEW
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_COMPACT_BYTES_VIEW

#pragma once

#include "compact_bytes_view_decl.h"
#include "compact_flag.h"

namespace abc::ethereum::trie
{

constexpr compact_bytes_view::compact_bytes_view(abc::byte const * data, std::size_t size) noexcept : view_{data, size}
{
}

constexpr auto
compact_bytes_view::flag() const noexcept -> compact_flag
{
    return static_cast<compact_flag>((view_[0] & 0xF0) >> 4);
}

constexpr auto
compact_bytes_view::size() const noexcept -> size_type
{
    return view_.size();
}

constexpr auto
compact_bytes_view::empty() const noexcept -> bool
{
    return view_.empty();
}

constexpr auto
compact_bytes_view::data() const noexcept -> const_pointer
{
    return view_.data();
}

constexpr auto
compact_bytes_view::begin() const noexcept -> const_iterator
{
    return view_.begin();
}

constexpr auto
compact_bytes_view::end() const noexcept -> const_iterator
{
    return view_.end();
}

constexpr auto
compact_bytes_view::operator[](size_type pos) const noexcept -> const_reference
{
    return view_[pos];
}

constexpr auto
compact_bytes_view::at(size_type pos) const -> const_reference
{
    return view_.at(pos);
}

constexpr auto
compact_bytes_view::front() const noexcept -> const_reference
{
    return view_.front();
}

constexpr auto
compact_bytes_view::back() const noexcept -> const_reference
{
    return view_.back();
}

constexpr auto
odd(compact_bytes_view view) noexcept -> bool
{
    return odd(view.flag());
}

constexpr auto
even(compact_bytes_view view) noexcept -> bool
{
    return even(view.flag());
}

constexpr auto
extension(compact_bytes_view view) noexcept -> bool
{
    return extension(view.flag());
}

constexpr auto
leaf(compact_bytes_view view) noexcept -> bool
{
    return leaf(view.flag());
}

} // namespace abc::ethereum::trie

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_COMPACT_BYTES_VIEW
