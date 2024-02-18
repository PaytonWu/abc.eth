// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_PACK)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_PACK

#pragma once

#include "pack_decl.h"
#include "codec_operator.h"

#include <abc/byte.h>
#include <abc/converter.h>
#include <abc/ethereum/types/address.h>
#include <abc/fixed_bytes.h>
#include <abc/fixed_hash.h>

#include <concepts>
#include <cstdint>
#include <span>
#include <string_view>

namespace abc::ethereum::rlp
{

template <packing_stream Stream>
packer<Stream>::packer(Stream & stream) noexcept : stream_{stream}
{
}

template <packing_stream Stream>
auto
packer<Stream>::pack_string_view(std::string_view input) -> packer &
{
    bytes_t bytes;
    encode_bytes(bytes_view_t{input}, bytes);
    append_buffer(bytes);
    return *this;
}

template <packing_stream Stream>
template <byte_numbering ByteNumbering>
auto
packer<Stream>::pack_bytes_view(bytes_view<ByteNumbering> input) -> packer &
{
    bytes_t bytes;
    encode_bytes(input, bytes);
    append_buffer(bytes);
    return *this;
}

template <packing_stream Stream>
template <byte_numbering ByteNumbering>
auto
packer<Stream>::pack_bytes(bytes<ByteNumbering> const & input) -> packer &
{
    bytes_t bytes;
    encode_bytes(bytes_view_t{input}, bytes);
    append_buffer(bytes);
    return *this;
}

template <packing_stream Stream>
auto
packer<Stream>::pack_address(types::address const & address) -> packer &
{
    bytes_t bytes;
    encode_bytes(bytes_view_t{address.bytes()}, bytes);
    append_buffer(bytes);
    return *this;
}

template <packing_stream Stream>
auto
packer<Stream>::pack_uint128(uint128_t const value) -> packer &
{
    auto number = value.export_bits_compact<abc::byte_numbering::msb0>().to<abc::byte_numbering::none>();
    bytes_t bytes;

    encode_bytes(number, bytes);
    append_buffer(bytes);
    return *this;
}

template <packing_stream Stream>
template <std::unsigned_integral T>
auto
packer<Stream>::pack_unsigned_integral(T const value) -> packer &
{
    auto const number = convert_to<bytes_be_t>::from(value).transform([](auto && bytes_be) { return bytes_be.template to<byte_numbering::none>(); }).value();
    bytes_t bytes;

    encode_bytes(number, bytes);
    append_buffer(bytes);
    return *this;
}

template <packing_stream Stream>
template <std::size_t N, byte_numbering ByteNumbering>
auto
packer<Stream>::pack_fixed_bytes(fixed_bytes<N, ByteNumbering> const & value) -> packer &
{
    bytes_t bytes;
    encode_bytes(bytes_view_t{value}, bytes);
    append_buffer(bytes);
    return *this;
}

template <packing_stream Stream>
template <typename T>
auto
packer<Stream>::pack_optional(std::optional<T> const & object) -> packer &
{
    if (object.has_value())
    {
        return pack(object.value());
    }

    return *this;
}

template <packing_stream Stream>
template <typename T>
    requires(!std::same_as<T, std::string_view>) && (!std::same_as<T, bytes_view_t>) && (!std::same_as<T, bytes_be_view_t>) && (!std::same_as<T, bytes_le_view_t>) &&
            (!std::same_as<T, bytes_t>) && (!std::same_as<T, bytes_be_t>) && (!std::same_as<T, bytes_le_t>) && (!std::same_as<T, types::address>) &&
            (!std::same_as<T, uint128_t>) && (!std::same_as<T, std::uint8_t>) && (!std::same_as<T, std::uint16_t>) && (!std::same_as<T, std::uint32_t>) &&
            (!std::same_as<T, std::uint64_t>) && (!std::same_as<T, std::optional<T>>)
auto
packer<Stream>::pack(T const & object) -> packer &
{
    simple_buffer object_buffer{};
    packer packer{object_buffer};

    packer << object;

    bytes_t bytes;
    encode_length(object_buffer.bytes_view().size(), 0xc0, bytes);

    append_buffer(bytes);
    append_buffer(object_buffer.bytes_view());

    return *this;
}

template <packing_stream Stream>
template <typename T>
    requires std::same_as<T, std::string_view>
auto
packer<Stream>::pack(T const object) -> packer &
{
    return pack_string_view(object);
}

template <packing_stream Stream>
template <typename T>
    requires std::same_as<T, bytes_view_t>
auto
packer<Stream>::pack(T const object) -> packer &
{
    return pack_bytes_view(object);
}

template <packing_stream Stream>
template <typename T>
    requires std::same_as<T, bytes_be_view_t>
auto
packer<Stream>::pack(T const object) -> packer &
{
    return pack_bytes_view(object);
}

template <packing_stream Stream>
template <typename T>
    requires std::same_as<T, bytes_le_view_t>
auto
packer<Stream>::pack(T const object) -> packer &
{
    return pack_bytes_view(object);
}

template <packing_stream Stream>
template <typename T>
    requires std::same_as<T, bytes_t>
auto
packer<Stream>::pack(T const & object) -> packer &
{
    return pack_bytes(object);
}

template <packing_stream Stream>
template <typename T>
    requires std::same_as<T, bytes_be_t>
auto
packer<Stream>::pack(T const & object) -> packer &
{
    return pack_bytes(object);
}

template <packing_stream Stream>
template <typename T>
    requires std::same_as<T, bytes_le_t>
auto
packer<Stream>::pack(T const & object) -> packer &
{
    return pack_bytes(object);
}

template <packing_stream Stream>
template <typename T>
    requires std::same_as<T, types::address>
auto
packer<Stream>::pack(T const & object) -> packer &
{
    return pack_address(object);
}

template <packing_stream Stream>
template <typename T>
    requires std::same_as<T, uint128_t>
auto
packer<Stream>::pack(T const object) -> packer &
{
    return pack_uint128(object);
}

template <packing_stream Stream>
template <typename T>
    requires std::same_as<T, std::uint8_t>
auto
packer<Stream>::pack(T const object) -> packer &
{
    return pack_unsigned_integral(object);
}

template <packing_stream Stream>
template <typename T>
    requires std::same_as<T, std::uint16_t>
auto
packer<Stream>::pack(T const object) -> packer &
{
    return pack_unsigned_integral(object);
}

template <packing_stream Stream>
template <typename T>
    requires std::same_as<T, std::uint32_t>
auto
packer<Stream>::pack(T const object) -> packer &
{
    return pack_unsigned_integral(object);
}

template <packing_stream Stream>
template <typename T>
    requires std::same_as<T, std::uint64_t>
auto
packer<Stream>::pack(T const object) -> packer &
{
    return pack_unsigned_integral(object);
}

template <packing_stream Stream>
template <std::size_t N, byte_numbering ByteNumbering>
auto
packer<Stream>::pack(fixed_bytes<N, ByteNumbering> const & object) -> packer &
{
    return pack_fixed_bytes(object);
}

template <packing_stream Stream>
template <typename T>
auto
packer<Stream>::pack(std::optional<T> const & object) -> packer &
{
    return pack_optional(object);
}

template <packing_stream Stream>
auto
packer<Stream>::encode_length(uint64_t length, uint32_t offset, bytes_t & output) -> void
{
    if (length < 56)
    {
        output.push_back(static_cast<byte>(length + offset));
        return;
    }

    if (length < std::numeric_limits<uint64_t>::max())
    {
        auto be_length = convert_to<bytes_be_t>::from(length).value();
        output.push_back(static_cast<byte>(be_length.size() + offset + 55));
        output += be_length.to<byte_numbering::none>();
        return;
    }

    unreachable();
}

template <packing_stream Stream>
auto
packer<Stream>::encode_bytes(bytes_view_t input, bytes_t & output) -> void
{
    if (input.size() == 1 && input[0] < 0x80)
    {
        output.push_back(input[0]);
        return;
    }

    encode_length(input.size(), 0x80, output);
    output += input;
}

template <packing_stream Stream>
auto
packer<Stream>::encode_bytes(bytes_be_view_t input, bytes_t & output) -> void
{
    if (input.size() == 1 && input[0] < 0x80)
    {
        output.push_back(input[0]);
        return;
    }

    encode_length(input.size(), 0x80, output);
    output += bytes_view_t{input};
}

template <packing_stream Stream>
auto
packer<Stream>::encode_bytes(bytes_le_view_t input, bytes_t & output) -> void
{
    if (input.size() == 1 && input[0] < 0x80)
    {
        output.push_back(input[0]);
        return;
    }

    encode_length(input.size(), 0x80, output);
    output += bytes_view_t{input};
}

template <packing_stream Stream>
auto
packer<Stream>::append_buffer(bytes_view_t const input) -> void
{
    stream_.append(input);
}

} // namespace abc::ethereum::rlp

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_PACK
