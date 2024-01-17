// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/trie/encoding.h>

#include <cassert>

namespace abc::ethereum::trie
{

auto
key_bytes_to_hex(bytes_view_t key) -> bytes_t
{
    auto const key_size = key.size();
    auto const key_size_in_hex = key_size * 2;
    auto const key_size_in_hex_with_terminator = key_size_in_hex + 1;

    auto hex_bytes = bytes_t{};
    hex_bytes.reserve(key_size_in_hex_with_terminator);

    for (auto b: key)
    {
        auto const high = static_cast<abc::byte>(b >> 4);
        auto const low = static_cast<abc::byte>(b & 0x0F);

        hex_bytes.push_back(high);
        hex_bytes.push_back(low);
    }

    hex_bytes.push_back(0x10);

    return hex_bytes;
}

auto
hex_to_key_bytes(bytes_view_t hex) -> expected<bytes_t, std::error_code>
{
    if (has_terminator(hex))
    {
        hex = hex.subview(0, hex.size() - 1);
    }

    if (hex.size() % 2 != 0)
    {
        return make_unexpected(std::make_error_code(std::errc::invalid_argument));
    }

    return decode_nibbles(hex);
}

auto
decode_nibbles(bytes_view_t nibbles) -> bytes_t
{
    assert(nibbles.size() % 2 == 0);

    auto const nibbles_size = nibbles.size();
    auto const bytes_size = nibbles_size / 2;

    auto bytes = bytes_t{};
    bytes.reserve(bytes_size);

    for (auto i = 0u; i < nibbles_size; i += 2)
    {
        auto const high = nibbles[i];
        auto const low = nibbles[i + 1];

        assert(high < 16);
        assert(low < 16);

        auto const byte = static_cast<abc::byte>((high << 4) | low);

        bytes.push_back(byte);
    }

    return bytes;
}

auto
has_terminator(bytes_view_t nibbles) -> bool
{
    return !nibbles.empty() && nibbles.back() == 0x10;
}

} // namespace abc::ethereum::trie
