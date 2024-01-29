// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NIBBLE_BYTES
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NIBBLE_BYTES

#pragma once

#include "nibble_bytes_fwd_decl.h"

#include <abc/bytes.h>

#include <vector>

namespace abc::ethereum::trie
{

class nibble_bytes
{
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

public:
    nibble_bytes() = default;

    nibble_bytes(bytes_view_t bytes_view);

    [[nodiscard]] auto
    has_terminator() const noexcept -> bool;

    [[nodiscard]] auto
    size() const noexcept -> std::size_t;

    [[nodiscard]] auto
    nibbles() const noexcept -> bytes_t const &;

    [[nodiscard]] auto
    nibbles() noexcept -> bytes_t &;

    [[nodiscard]] auto
    nibbles_view() const noexcept -> bytes_view_t;

    [[nodiscard]] auto
    nibbles_view(std::size_t offset) const noexcept -> bytes_view_t;

    [[nodiscard]] auto
    nibbles_view(std::size_t offset, std::size_t count) const noexcept -> bytes_view_t;
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_NIBBLE_BYTES
