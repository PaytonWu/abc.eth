// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/trie/nibble_bytes.h>

namespace abc::ethereum::trie
{

auto
nibble_bytes::to_bytes() const -> expected<abc::bytes_t, std::error_code>
{
    return static_cast<nibble_bytes_view>(*this).to_bytes();
}

}
