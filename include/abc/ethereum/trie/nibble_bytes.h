// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NIBBLE_BYTES
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NIBBLE_BYTES

#pragma once

#include "nibble_bytes_fwd_decl.h"
#include "nibble_bytes_view.h"

#include <abc/bytes.h>
#include <abc/error.h>
#include <abc/expected.h>

#include <range/v3/view/enumerate.hpp>

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
    explicit constexpr nibble_bytes(bytes_view_t bytes_view) : nibbles_(bytes_view.empty() ? 0zu : bytes_view.size() * 2 + 1)
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

    explicit constexpr nibble_bytes(std::initializer_list<byte> il) : nibbles_(static_cast<bool>(il.size()) ? il.size() * 2 + 1 : 0uz)
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

public:
    nibble_bytes() = default;

    static constexpr auto
    from(bytes_view_t bytes_view) -> nibble_bytes
    {
        return nibble_bytes{bytes_view};
    }

    static constexpr auto
    from(std::initializer_list<byte> il) -> nibble_bytes
    {
        return nibble_bytes{il};
    }

    auto
    to_bytes() const -> expected<abc::bytes_t, std::error_code>;

    [[nodiscard]] constexpr auto
    has_terminator() const noexcept -> bool
    {
        return !nibbles_.empty() && nibbles_.back() == terminator;
    }

    [[nodiscard]] constexpr auto
    size() const noexcept -> std::size_t
    {
        return nibbles_.size();
    }

    [[nodiscard]] constexpr auto
    empty() const noexcept -> bool
    {
        return size() == 0;
    }

    constexpr
    operator nibble_bytes_view() const noexcept
    {
        return nibble_bytes_view{nibbles_.data(), nibbles_.size()};
    }

    [[nodiscard]] constexpr auto
    nibbles_view(std::size_t offset, std::size_t count = npos) const -> nibble_bytes_view
    {
        if (offset > nibbles_.size())
        {
            abc::throw_exception<std::out_of_range>("abc::ethereum::trie::nibble_bytes::nibbles_view: offset out of range");
        }
        return nibble_bytes_view{nibbles_.data() + offset, std::min(count, nibbles_.size() - offset)};
    }

    //    [[nodiscard]] constexpr auto
    //    begin() noexcept -> iterator
    //    {
    //        return nibbles_.begin();
    //    }

    [[nodiscard]] constexpr auto
    begin() const noexcept -> const_iterator
    {
        return nibbles_.begin();
    }

    [[nodiscard]] constexpr auto
    cbegin() const noexcept -> const_iterator
    {
        return nibbles_.cbegin();
    }

    //    [[nodiscard]] constexpr auto
    //    end() noexcept -> iterator
    //    {
    //        return nibbles_.end();
    //    }

    [[nodiscard]] constexpr auto
    end() const noexcept -> const_iterator
    {
        return nibbles_.end();
    }

    [[nodiscard]] constexpr auto
    cend() const noexcept -> const_iterator
    {
        return nibbles_.cend();
    }

    //    [[nodiscard]] constexpr auto
    //    operator[](std::size_t index) -> reference
    //    {
    //        return nibbles_[index];
    //    }

    [[nodiscard]] constexpr auto
    operator[](std::size_t index) const -> const_reference
    {
        return nibbles_[index];
    }

    //    [[nodiscard]] constexpr auto
    //    front() -> reference
    //    {
    //        return nibbles_.front();
    //    }

    [[nodiscard]] constexpr auto
    front() const -> const_reference
    {
        return nibbles_.front();
    }

    //    [[nodiscard]] constexpr auto
    //    back() -> reference
    //    {
    //        return nibbles_.back();
    //    }

    [[nodiscard]] constexpr auto
    back() const -> const_reference
    {
        return nibbles_.back();
    }

    [[nodiscard]] constexpr auto
    first(size_t const count) const noexcept -> nibble_bytes_view
    {
        assert(count <= nibbles_.size());
        return nibble_bytes_view{std::addressof(nibbles_[0]), count};
    }

    [[nodiscard]] constexpr auto
    last(size_t const count) const noexcept -> nibble_bytes_view
    {
        assert(count <= nibbles_.size());
        return nibble_bytes_view{std::addressof(nibbles_[size() - count]), count};
    }

    [[nodiscard]] constexpr auto
    operator==(nibble_bytes const & other) const noexcept -> bool = default;
};

} // namespace abc::ethereum::trie

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NIBBLE_BYTES
