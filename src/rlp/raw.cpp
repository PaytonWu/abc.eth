// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/rlp/raw.h>

#include <abc/ethereum/rlp/error.h>

namespace abc::ethereum::rlp
{

auto
read_size(bytes_view_t buf, byte size_of_length) -> expected<std::uint64_t, std::error_code>
{
    if (buf.size() < static_cast<std::size_t>(size_of_length))
    {
        return make_unexpected(make_error_code(errc::unexpected_eof));
    }

    std::uint64_t s{0};
    switch (size_of_length)
    {
        case static_cast<byte>(1):
            s = static_cast<std::uint64_t>(buf[0]);
            break;
        case static_cast<byte>(2):
            s = static_cast<std::uint64_t>(buf[0]) << 8 | static_cast<std::uint64_t>(buf[1]);
            break;
        case static_cast<byte>(3):
            s = static_cast<std::uint64_t>(buf[0]) << 16 | static_cast<std::uint64_t>(buf[1]) << 8 | static_cast<std::uint64_t>(buf[2]);
            break;
        case static_cast<byte>(4):
            s = static_cast<std::uint64_t>(buf[0]) << 24 | static_cast<std::uint64_t>(buf[1]) << 16 | static_cast<std::uint64_t>(buf[2]) << 8 | static_cast<std::uint64_t>(buf[3]);
            break;
        case static_cast<byte>(5):
            s = static_cast<std::uint64_t>(buf[0]) << 32 | static_cast<std::uint64_t>(buf[1]) << 24 | static_cast<std::uint64_t>(buf[2]) << 16 |
                static_cast<std::uint64_t>(buf[3]) << 8 | static_cast<std::uint64_t>(buf[4]);
            break;
        case static_cast<byte>(6):
            s = static_cast<std::uint64_t>(buf[0]) << 40 | static_cast<std::uint64_t>(buf[1]) << 32 | static_cast<std::uint64_t>(buf[2]) << 24 |
                static_cast<std::uint64_t>(buf[3]) << 16 | static_cast<std::uint64_t>(buf[4]) << 8 | static_cast<std::uint64_t>(buf[5]);
            break;
        case static_cast<byte>(7):
            s = static_cast<std::uint64_t>(buf[0]) << 48 | static_cast<std::uint64_t>(buf[1]) << 40 | static_cast<std::uint64_t>(buf[2]) << 32 |
                static_cast<std::uint64_t>(buf[3]) << 24 | static_cast<std::uint64_t>(buf[4]) << 16 | static_cast<std::uint64_t>(buf[5]) << 8 | static_cast<std::uint64_t>(buf[6]);
            break;
        case static_cast<byte>(8):
            s = static_cast<std::uint64_t>(buf[0]) << 56 | static_cast<std::uint64_t>(buf[1]) << 48 | static_cast<std::uint64_t>(buf[2]) << 40 |
                static_cast<std::uint64_t>(buf[3]) << 32 | static_cast<std::uint64_t>(buf[4]) << 24 | static_cast<std::uint64_t>(buf[5]) << 16 |
                static_cast<std::uint64_t>(buf[6]) << 8 | static_cast<std::uint64_t>(buf[7]);
    }
    // Reject sizes < 56 (shouldn't have separate size) and sizes with
    // leading zero bytes.
    if (s < 56 || buf[0] == 0)
    {
        return make_unexpected(make_error_code(errc::non_canonical_size));
    }

    return s;
}

auto
read_kind(bytes_view_t buf) -> expected<decoded_type_and_size, std::error_code>
{
    auto const sz = buf.size();
    if (sz == 0)
    {
        return make_unexpected(make_error_code(errc::unexpected_eof));
    }

    auto const b = buf[0];
    decoded_type_and_size result;

    if (b < 0x80)
    {
        result.type = type::byte;
        result.tag_size = 0;
        result.content_size = 1;
    }
    else if (b < 0xB8)
    {
        result.type = type::bytes;
        result.tag_size = 1;
        result.content_size = b - 0x80;

        if (result.content_size == 1 && sz > 1 && buf[1] < 128)
        {
            return make_unexpected(make_error_code(errc::non_canonical_size));
        }
    }
    else if (b < 0xC0)
    {
        result.type = type::bytes;
        result.tag_size = b - 0xB7;
        auto const sr = read_size(buf.subview(1), b - 0xB7);
        if (sr.is_err())
        {
            return make_unexpected(sr.error());
        }
        result.content_size = sr.value();
    }
    else if (b < 0xF8)
    {
        result.type = type::list;
        result.tag_size = 1;
        result.content_size = b - 0xC0;
    }
    else
    {
        result.type = type::list;
        result.tag_size = b - 0xF7;
        auto const sr = read_size(buf.subview(1), b - 0xF7);
        if (sr.is_err())
        {
            return make_unexpected(sr.error());
        }
        result.content_size = sr.value();
    }

    return result;
}

auto
split(bytes_view_t buf) -> expected<decoded_item, std::error_code>
{
    return read_kind(buf).transform([buf](decoded_type_and_size const & dts) -> decoded_item {
        return decoded_item{.type = dts.type, .content = buf.subview(dts.tag_size, dts.content_size),  .rest = buf.subview(dts.tag_size + dts.content_size)};
    });
}

auto
split_bytes(bytes_view_t buf) -> expected<decoded_item, std::error_code>
{
    auto split_result = split(buf);
    if (split_result.is_err())
    {
        return split_result;
    }

    if (split_result.value().type == type::list)
    {
        return make_unexpected(make_error_code(errc::expected_bytes));
    }

    return split_result;
}

} // namespace abc::ethereum::rlp
