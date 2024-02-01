// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/trie/encoding.h>

namespace abc::ethereum::trie
{

auto
nibble_bytes_to_key_bytes(nibble_bytes_view nibble_bytes_view) -> expected<abc::bytes_t, std::error_code>
{
    return nibble_bytes_view.to_bytes<abc::bytes_t>();
}

} // namespace abc::ethereum::trie
