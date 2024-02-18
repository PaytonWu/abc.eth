// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_PACK_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_PACK_DECL

#pragma once

#include "pack_fwd_decl.h"
#include "simple_buffer.h"

// #include <abc/ethereum/types/address_fwd_decl.h>

#include <abc/uint128.h>

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

    explicit packer(Stream & stream) noexcept;

    auto
    pack_string_view(std::string_view input) -> packer &;

    template <byte_numbering ByteNumbering>
    auto
    pack_bytes_view(bytes_view<ByteNumbering> input) -> packer &;

    template <byte_numbering ByteNumbering>
    auto
    pack_bytes(bytes<ByteNumbering> const & input) -> packer &;

//    auto
//    pack_address(types::address const & address) -> packer &;

    auto
    pack_uint128(uint128_t const value) -> packer &;

    template <std::unsigned_integral T>
    auto
    pack_unsigned_integral(T const value) -> packer &;

    template <std::size_t N, byte_numbering ByteNumbering>
    auto
    pack_bytes(fixed_bytes<N, ByteNumbering> const & value) -> packer &;

    template <typename T>
    auto
    pack_optional(std::optional<T> const & object) -> packer &;

    template <typename T>
        requires (!std::same_as<T, std::string_view>) &&
                (!std::same_as<T, bytes_view_t>) &&
                (!std::same_as<T, bytes_be_view_t>) &&
                (!std::same_as<T, bytes_le_view_t>) &&
                (!std::same_as<T, bytes_t>) &&
                (!std::same_as<T, bytes_be_t>) &&
                (!std::same_as<T, bytes_le_t>) &&
                // (!std::same_as<T, types::address>) &&
                (!std::same_as<T, uint128_t>) &&
                (!std::same_as<T, std::uint8_t>) &&
                (!std::same_as<T, std::uint16_t>) &&
                (!std::same_as<T, std::uint32_t>) &&
                (!std::same_as<T, std::uint64_t>) &&
                (!std::same_as<T, std::optional<T>>)
    auto
    pack(T const & object) -> packer &;

    template <typename T> requires std::same_as<T, std::string_view>
    auto
    pack(T const object) -> packer &;

    template <typename T> requires std::same_as<T, bytes_view_t>
    auto
    pack(T const object) -> packer &;

    template <typename T> requires std::same_as<T, bytes_be_view_t>
    auto
    pack(T const object) -> packer &;

    template <typename T> requires std::same_as<T, bytes_le_view_t>
    auto
    pack(T const object) -> packer &;

//    template <typename T> requires std::same_as<T, bytes_t>
//    auto
//    pack(T const & object) -> packer &;

    template <typename T> requires std::same_as<T, bytes_be_t>
    auto
    pack(T const & object) -> packer &;

    template <typename T> requires std::same_as<T, bytes_le_t>
    auto
    pack(T const & object) -> packer &;

//    template <typename T> requires std::same_as<T, types::address>
//    auto
//    pack(T const & object) -> packer &;

//    template <typename T> requires std::same_as<T, uint128_t>
//    auto
//    pack(T const object) -> packer &;

    template <typename T> requires std::same_as<T, std::uint8_t>
    auto
    pack(T const object) -> packer &;

    template <typename T> requires std::same_as<T, std::uint16_t>
    auto
    pack(T const object) -> packer &;

    template <typename T> requires std::same_as<T, std::uint32_t>
    auto
    pack(T const object) -> packer &;

    template <typename T> requires std::same_as<T, std::uint64_t>
    auto
    pack(T const object) -> packer &;

//    template <std::size_t N, byte_numbering ByteNumbering>
//    auto
//    pack(fixed_bytes<N, ByteNumbering> const & object) -> packer &;

    template <typename T>
    auto
    pack(std::optional<T> const & object) -> packer &;

private:
    auto
    encode_length(uint64_t length, uint32_t offset, bytes_t & output) -> void;

    auto
    encode_bytes(bytes_view_t input, bytes_t & output) -> void;

    auto
    encode_bytes(bytes_be_view_t input, bytes_t & output) -> void;

    auto
    encode_bytes(bytes_le_view_t input, bytes_t & output) -> void;

    auto
    append_buffer(bytes_view_t const input) -> void;
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_PACK_DECL
