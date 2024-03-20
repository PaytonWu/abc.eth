// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_COMPACT_BYTES_DECL
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_COMPACT_BYTES_DECL

#pragma once

#include "compact_bytes_fwd_decl.h"

#include "compact_bytes_view_decl.h"
#include "compact_flag_decl.h"
#include "nibble_bytes_fwd_decl.h"
#include "nibble_bytes_view.h"

#include <abc/byte.h>

#include <vector>

namespace abc::ethereum::trie
{

class compact_bytes
{
private:
    friend class nibble_bytes;

    using bytes_t = std::vector<abc::byte>;
    bytes_t bytes_{};

public:
    using value_type = bytes_t::value_type;
    using size_type = bytes_t::size_type;
    using difference_type = bytes_t::difference_type;
    using pointer = bytes_t::pointer;
    using const_pointer = bytes_t::const_pointer;
    using reference = bytes_t::reference;
    using const_reference = bytes_t::const_reference;
    using iterator = bytes_t::iterator;
    using const_iterator = bytes_t::const_iterator;
    using reverse_iterator = bytes_t::reverse_iterator;
    using const_reverse_iterator = bytes_t::const_reverse_iterator;

private:

public:
    constexpr compact_bytes(nibble_bytes_view view);
    constexpr compact_bytes(bytes_view_t view);

    constexpr auto
    flag() const noexcept -> compact_flag;

    constexpr operator compact_bytes_view() const noexcept;

    constexpr auto
    size() const noexcept -> size_type;

    constexpr auto
    empty() const noexcept -> bool;

    constexpr auto
    data() const noexcept -> const_pointer;

    constexpr auto
    begin() const noexcept -> const_iterator;

    constexpr auto
    end() const noexcept -> const_iterator;

    constexpr auto
    cbegin() const noexcept -> const_iterator;

    constexpr auto
    cend() const noexcept -> const_iterator;

    friend constexpr auto
    operator==(compact_bytes const & lhs, compact_bytes const & rhs) noexcept -> bool = default;
};


}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_COMPACT_BYTES_DECL
