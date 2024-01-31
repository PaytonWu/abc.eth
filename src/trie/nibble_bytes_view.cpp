// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/trie/nibble_bytes_view.h>

namespace abc::ethereum::trie
{

auto
nibble_bytes_view::to_bytes() const -> expected<abc::bytes_t, std::error_code>
{
    auto view_copy = view_;
    if (has_termintor())
    {
        view_copy = view_copy.substr(0, view_copy.size() - 1);
    }

    if (view_copy.size() % 2 != 0)
    {
        return make_unexpected(std::make_error_code(std::errc::invalid_argument));
    }

    auto const nibbles_size = view_.size();
    auto const bytes_size = nibbles_size / 2;

    auto bytes = abc::bytes_t{};
    bytes.reserve(bytes_size);

    for (auto i = 0u; i < bytes_size; ++i)
    {
        auto const high = view_[2 * i];
        auto const low = view_[2 * i + 1];

        assert(high < 16);
        assert(low < 16);

        auto const byte = static_cast<abc::byte>((high << 4) | low);

        bytes.push_back(byte);
    }

    return bytes;
}

}
