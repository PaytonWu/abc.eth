// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_PACK_DECL)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_PACK_DECL

#pragma once

#include "pack_fwd_decl.h"
#include "simple_buffer.h"

#include <abc/bytes.h>
#include <abc/fixed_bytes.h>
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
    packer(packer &&) = default;
    ~packer() = default;

    auto
    operator=(packer const &) -> packer & = delete;

    auto
    operator=(packer &&) -> packer & = default;

    explicit packer(Stream & stream) noexcept;

    auto
    pack_string_view(std::string_view input) -> packer &;

    template <byte_numbering ByteNumbering>
    auto
    pack_bytes_view(bytes_view<ByteNumbering> input) -> packer &;

    template <byte_numbering ByteNumbering>
    auto
    pack_bytes(bytes<ByteNumbering> const & input) -> packer &;

    auto
    pack_uint128(uint128_t value) -> packer &;

    template <std::unsigned_integral T>
    auto
    pack_unsigned_integral(T value) -> packer &;

    template <std::size_t N, byte_numbering ByteNumbering>
    auto
    pack_bytes(fixed_bytes<N, ByteNumbering> const & value) -> packer &;

    auto
    pack_empty_bytes() -> packer &;

    auto
    pack_empty_list() -> packer &;

    template <typename T>
    auto
    pack(T const & object) -> packer &;

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
    append_buffer(bytes_view_t input) -> void;

    auto
    append_empty_bytes() -> void;

    auto
    append_empty_list() -> void;
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_PACK_DECL
