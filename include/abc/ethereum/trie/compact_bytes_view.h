// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_COMPACT_BYTES_VIEW
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_COMPACT_BYTES_VIEW

#pragma once

#include "compact_bytes_view_decl.h"

namespace abc::ethereum::trie
{

constexpr compact_bytes_view::compact_bytes_view(abc::byte const * data, std::size_t size) noexcept : view_{data, size}
{
}

[[nodiscard]] constexpr auto
compact_bytes_view::size() const noexcept -> size_type
{
    return view_.size();
}

[[nodiscard]] constexpr auto
compact_bytes_view::empty() const noexcept -> bool
{
    return view_.empty();
}

[[nodiscard]] constexpr auto
compact_bytes_view::data() const noexcept -> const_pointer
{
    return view_.data();
}

[[nodiscard]] constexpr auto
compact_bytes_view::begin() const noexcept -> const_iterator
{
    return view_.begin();
}

[[nodiscard]] constexpr auto
compact_bytes_view::end() const noexcept -> const_iterator
{
    return view_.end();
}

[[nodiscard]] constexpr auto
compact_bytes_view::operator[](size_type pos) const noexcept -> const_reference
{
    return view_[pos];
}

[[nodiscard]] constexpr auto
compact_bytes_view::at(size_type pos) const -> const_reference
{
    return view_.at(pos);
}

[[nodiscard]] constexpr auto
compact_bytes_view::front() const noexcept -> const_reference
{
    return view_.front();
}

[[nodiscard]] constexpr auto
compact_bytes_view::back() const noexcept -> const_reference
{
    return view_.back();
}

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_COMPACT_BYTES_VIEW
