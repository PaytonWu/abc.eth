// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_PACK)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_PACK

#pragma once

#include "pack_decl.h"
#include "sbuffer.h"
#include "codec_operator.h"

#include <abc/byte.h>
#include <abc/converter.h>
#include <abc/ethereum/types/address.h>
#include <abc/fixed_bytes.h>
#include <abc/fixed_hash.h>
#include <abc/uint128.h>

#include <cstdint>
#include <concepts>
#include <span>
#include <string_view>

namespace abc::ethereum::rlp
{

template <packing_stream Stream>
class packer
{
private:
    Stream & stream_;

public:
    packer() = delete;

    packer(packer const &) = delete;

    auto
    operator=(packer const &) -> packer & = delete;

    packer(packer &&) = default;

    auto
    operator=(packer &&) -> packer & = default;

    ~packer() = default;

    explicit packer(Stream & stream) noexcept : stream_{ stream }
    {
    }

    auto
    pack(std::string_view input) -> packer &
    {
        bytes_t bytes;
        encode_bytes(bytes_view_t{ input }, bytes);
        append_buffer(bytes);
        return *this;
    }

    auto
    pack(bytes_view_t input) -> packer &
    {
        bytes_t bytes;
        encode_bytes(input, bytes);
        append_buffer(bytes);
        return *this;
    }

    auto
    pack(bytes_be_view_t input) -> packer &
    {
        bytes_t bytes;
        encode_bytes(input, bytes);
        append_buffer(bytes);
        return *this;
    }

    auto
    pack(bytes_le_view_t input) -> packer &
    {
        bytes_t bytes;
        encode_bytes(input, bytes);
        append_buffer(bytes);
        return *this;
    }

    auto
    pack(types::address const & address) -> packer &
    {
        bytes_t bytes;
        encode_bytes(bytes_view_t{ address.bytes() }, bytes);
        append_buffer(bytes);
        return *this;
    }

    auto
    pack(uint128_t const value) -> packer &
    {
        auto number = value.export_bits_compact<abc::byte_numbering::msb0>().to<abc::byte_numbering::none>();
        bytes_t bytes;

        encode_bytes(number, bytes);
        append_buffer(bytes);
        return *this;
    }

    template <std::unsigned_integral T>
    auto
    pack(T const value) -> packer &
    {
        auto const number = convert_to<bytes_be_t>::from(value).transform([](auto && bytes_be) { return bytes_be.template to<byte_numbering::none>(); }).value();
        bytes_t bytes;

        encode_bytes(number, bytes);
        append_buffer(bytes);
        return *this;
    }

    template <std::size_t N, byte_numbering ByteNumbering>
    auto
    pack(fixed_bytes<N, ByteNumbering> const & value) -> packer &
    {
        bytes_t bytes;
        encode_bytes(bytes_view_t{ value }, bytes);
        append_buffer(bytes);
        return *this;
    }

    template <typename T> requires (!std::is_fundamental_v<T>)
    auto
    pack(T const & object) -> packer &
    {
        sbuffer object_buffer{};
        packer packer{ object_buffer };

        // object.serialize(packer);
        packer << object;

        bytes_t bytes;
        encode_length(object_buffer.bytes_view().size(), 0xc0, bytes);

        append_buffer(bytes);
        append_buffer(object_buffer.bytes_view());

        return *this;
    }

    template <typename T>
    auto
    pack(std::optional<T> const & object) -> packer &
    {
        if (object.has_value())
        {
            return pack(object.value());
        }

        return *this;
    }

//    auto
//    operator<<(std::string_view input) -> packer &
//    {
//        return pack(input);
//    }
//
//    auto
//    operator<<(bytes_view_t input) -> packer &
//    {
//        return pack(input);
//    }
//
//    auto
//    operator<<(types::address const & address) -> packer &
//    {
//        return pack(address);
//    }
//
//    auto
//    operator<<(uint128_t const input) -> packer &
//    {
//        return pack(input);
//    }
//
//    template <std::unsigned_integral T>
//    auto
//    operator<<(T const input) -> packer &
//    {
//        return pack(input);
//    }
//
//    template <std::size_t N, byte_numbering ByteNumbering>
//    auto
//    operator<<(fixed_bytes<N, ByteNumbering> const & input) -> packer &
//    {
//        return pack(input);
//    }
//
//    template <typename T>
//    requires serializable<T, packer>
//    auto
//    operator<<(T const & input) -> packer &
//    {
//        return pack(input);
//    }
//
//    template <typename T>
//    requires serializable<T, packer>
//    auto
//    operator<<(std::optional<T> const & input) -> packer &
//    {
//        return pack(input);
//    }

private:
    auto
    encode_length(uint64_t length, uint32_t offset, bytes_t & output) -> void
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

    auto
    encode_bytes(bytes_view_t input, bytes_t & output) -> void
    {
        if (input.size() == 1 && input[0] < 0x80)
        {
            output.push_back(input[0]);
            return;
        }

        encode_length(input.size(), 0x80, output);
        output += input;
    }

    auto
    encode_bytes(bytes_be_view_t input, bytes_t & output) -> void
    {
        if (input.size() == 1 && input[0] < 0x80)
        {
            output.push_back(input[0]);
            return;
        }

        encode_length(input.size(), 0x80, output);
        output += bytes_view_t{input };
    }

    auto
    encode_bytes(bytes_le_view_t input, bytes_t & output) -> void
    {
        if (input.size() == 1 && input[0] < 0x80)
        {
            output.push_back(input[0]);
            return;
        }

        encode_length(input.size(), 0x80, output);
        output += bytes_view_t{input };
    }

    auto
    append_buffer(bytes_view_t const input) -> void
    {
        stream_.append(input);
    }
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_PACK
