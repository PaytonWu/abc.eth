// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_COMPACT_BYTES
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_COMPACT_BYTES

#pragma once

#include "compact_bytes_decl.h"

#include "compact_bytes_view.h"
#include "nibble_bytes_view.h"

#include <abc/bytes_view.h>

#include <cassert>
#include <span>

namespace abc::ethereum::trie
{

constexpr compact_bytes::compact_bytes(nibble_bytes_view view)
{
    byte terminator{static_cast<byte>(0)};
    if (view.has_terminator())
    {
        terminator = static_cast<byte>(1);
        view = view.first(view.size() - 1);
    }
    bytes_.resize(view.size() / 2 + 1);

    bytes_[0] = static_cast<value_type>(terminator << 5);
    if (view.size() & 1)
    {
        bytes_[0] |= static_cast<value_type>(1 << 4);
        bytes_[0] |= static_cast<value_type>(view[0]);

        view = view.last(view.size() - 1);
    }
    assert(view.size() % 2 == 0);

    if (!view.empty())
    {
        std::span bytes_span{&bytes_[1], bytes_.size() - 1};
        auto const size = view.in_place_fill(bytes_span).expect("fill_bytes failed");
        assert(size == bytes_span.size());
    }
}

constexpr compact_bytes::compact_bytes(bytes_view_t view) : bytes_{view.begin(), view.end()}
{
}

constexpr auto
compact_bytes::flag() const noexcept -> compact_flag
{
    return static_cast<compact_flag>((bytes_[0] & 0xF0) >> 4);
}

constexpr compact_bytes::operator compact_bytes_view() const noexcept
{
    return compact_bytes_view{bytes_.data(), bytes_.size()};
}

constexpr auto
compact_bytes::size() const noexcept -> size_type
{
    return bytes_.size();
}

constexpr auto
compact_bytes::empty() const noexcept -> bool
{
    return bytes_.empty();
}

constexpr auto
compact_bytes::data() const noexcept -> const_pointer
{
    return bytes_.data();
}

constexpr auto
compact_bytes::begin() const noexcept -> const_iterator
{
    return bytes_.begin();
}

constexpr auto
compact_bytes::end() const noexcept -> const_iterator
{
    return bytes_.end();
}

constexpr auto
compact_bytes::cbegin() const noexcept -> const_iterator
{
    return bytes_.cbegin();
}

constexpr auto
compact_bytes::cend() const noexcept -> const_iterator
{
    return bytes_.cend();
}

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_COMPACT_BYTES
