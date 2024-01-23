// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/trie/nibble_bytes.h>

#include <range/v3/view/enumerate.hpp>

namespace abc::ethereum::trie
{

nibble_bytes::nibble_bytes(abc::bytes_view_t bytes_view)
    : nibbles_(bytes_view.size() * 2 + 1)
{
    for (auto [index, b]: ranges::views::enumerate(bytes_view))
    {
        auto const high = static_cast<abc::byte>(b >> 4);
        auto const low = static_cast<abc::byte>(b & 0x0F);

        nibbles_[index * 2] = high;
        nibbles_[index * 2 + 1] = low;
    }

    nibbles_.back() = 0x10;
}

}
