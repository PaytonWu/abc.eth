// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/trie/node_utility.h>

#include <abc/ethereum/trie/error.h>

#include <system_error>

namespace abc::ethereum::trie
{

auto
decode_node(h256_t const & hash, bytes_view_t buf) -> expected<std::shared_ptr<node_face>, std::error_code>
{
    if (buf.empty())
    {
        return make_unexpected(make_error_code(errc::unexpected_eof));
    }

    auto const type = buf[0] & 0xf0;
    switch (type)
    {
        case 0x00:
        case 0x20:
        case 0x40:
        case 0x60:
        case 0x80:
        case 0xa0:
        case 0xc0:
        case 0xe0:
            return must_decode_node(hash, buf);
        case 0xf0:
            return make_unexpected(std::make_error_code(std::errc::protocol_error));
        default:
            return make_unexpected(std::make_error_code(std::errc::protocol_error));
    }
}

}
