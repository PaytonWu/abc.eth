// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NIBBLE_BYTES
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NIBBLE_BYTES

#pragma once

#include "nibble_bytes_decl.h"

#include "compact_bytes_view.h"

#include <abc/bytes_view.h>

#include <range/v3/view/enumerate.hpp>

namespace abc::ethereum::trie
{

constexpr nibble_bytes::nibble_bytes(compact_bytes_view view)
{
    if (view.empty())
    {
        return;
    }

    nibble_bytes temp{bytes_view_t{view}};
    nibble_bytes_view temp_view{temp};

    if (temp_view[0] < static_cast<byte>(2))
    {
        temp_view = temp_view.first(temp_view.size() - 1);
    }

    size_type chop_index = 2u - (temp_view[0] & 1);
    nibbles_ = std::move(nibble_bytes{temp_view.last(temp_view.size() - chop_index)}.nibbles_);
}

constexpr nibble_bytes::nibble_bytes(bytes_view_t bytes_view) : nibbles_(bytes_view.empty() ? 0zu : bytes_view.size() * 2 + 1)
{
    for (auto [index, b] : ranges::views::enumerate(bytes_view))
    {
        auto const high = static_cast<abc::byte>(b >> 4);
        auto const low = static_cast<abc::byte>(b & 0x0F);

        nibbles_[index * 2] = high;
        nibbles_[index * 2 + 1] = low;
    }

    if (!nibbles_.empty())
    {
        nibbles_.back() = terminator;
    }
}

constexpr nibble_bytes::nibble_bytes(std::initializer_list<byte> il) : nibbles_(static_cast<bool>(il.size()) ? il.size() * 2 + 1 : 0uz)
{
    for (auto [index, b] : ranges::views::enumerate(il))
    {
        auto const high = static_cast<abc::byte>(b >> 4);
        auto const low = static_cast<abc::byte>(b & 0x0F);

        nibbles_[index * 2] = high;
        nibbles_[index * 2 + 1] = low;
    }

    if (!nibbles_.empty())
    {
        nibbles_.back() = terminator;
    }
}

constexpr nibble_bytes::nibble_bytes(abc::ethereum::trie::nibble_bytes_view view)
{
    nibbles_.resize(view.size());
    std::copy(view.begin(), view.end(), nibbles_.begin());
}

constexpr auto
nibble_bytes::from(bytes_view_t bytes_view) -> nibble_bytes
{
    return nibble_bytes{bytes_view};
}

constexpr auto
nibble_bytes::from(std::initializer_list<byte> il) -> nibble_bytes
{
    return nibble_bytes{il};
}

template <typename BytesT> // requires std::is_continuous_container_v<BytesT>
auto
nibble_bytes::to() const -> expected<BytesT, std::error_code>
{
    return static_cast<nibble_bytes_view>(*this).to<abc::bytes_t>();
}

constexpr auto
nibble_bytes::has_terminator() const noexcept -> bool
{
    return !nibbles_.empty() && nibbles_.back() == terminator;
}

constexpr auto
nibble_bytes::size() const noexcept -> std::size_t
{
    return nibbles_.size();
}

constexpr auto
nibble_bytes::empty() const noexcept -> bool
{
    return size() == 0;
}

constexpr nibble_bytes::operator nibble_bytes_view() const noexcept
{
    return nibble_bytes_view{nibbles_.data(), nibbles_.size()};
}

constexpr auto
nibble_bytes::nibbles_view(std::size_t offset, std::size_t count) const -> nibble_bytes_view
{
    if (offset > nibbles_.size())
    {
        abc::throw_exception<std::out_of_range>("abc::ethereum::trie::nibble_bytes::nibbles_view: offset out of range");
    }
    return nibble_bytes_view{nibbles_.data() + offset, std::min(count, nibbles_.size() - offset)};
}

constexpr auto
nibble_bytes::begin() const noexcept -> const_iterator
{
    return nibbles_.begin();
}

constexpr auto
nibble_bytes::cbegin() const noexcept -> const_iterator
{
    return nibbles_.cbegin();
}

constexpr auto
nibble_bytes::end() const noexcept -> const_iterator
{
    return nibbles_.end();
}

constexpr auto
nibble_bytes::cend() const noexcept -> const_iterator
{
    return nibbles_.cend();
}

constexpr auto
nibble_bytes::operator[](std::size_t index) const -> const_reference
{
    return nibbles_[index];
}

constexpr auto
nibble_bytes::front() const -> const_reference
{
    return nibbles_.front();
}

constexpr auto
nibble_bytes::back() const -> const_reference
{
    return nibbles_.back();
}

constexpr auto
nibble_bytes::first(size_t const count) const noexcept -> nibble_bytes_view
{
    assert(count <= nibbles_.size());
    return nibble_bytes_view{std::addressof(nibbles_[0]), count};
}

constexpr auto
nibble_bytes::last(size_t const count) const noexcept -> nibble_bytes_view
{
    assert(count <= nibbles_.size());
    return nibble_bytes_view{std::addressof(nibbles_[size() - count]), count};
}

} // namespace abc::ethereum::trie

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NIBBLE_BYTES
