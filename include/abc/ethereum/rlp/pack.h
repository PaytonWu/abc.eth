// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_PACK)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_PACK

#pragma once

#include "concepts.h"

#include <abc/byte.h>
#include <abc/converter.h>

#include <cstdint>
#include <concepts>
#include <span>
#include <string_view>

namespace abc::ethereum::rlp {

template <typename Stream>
class packer {
private:
    Stream & stream_;

public:
    packer() = delete;
    packer(packer const &) = delete;
    auto operator=(packer const &) -> packer & = delete;
    packer(packer &&) = default;
    auto operator=(packer &&) -> packer & = default;
    ~packer() = default;

    packer(Stream & stream) noexcept : stream_{ stream } {
    }

    template <std::integral T>
    auto pack_integer(T value) noexcept -> packer & {
        pack_integer_impl(value);
        return *this;
    }

    auto pack_string(std::string_view input) -> packer & {
        auto const bytes = encode_bytes(std::span{ reinterpret_cast<byte const *>(input.data()), input.size() });
        append_buffer(bytes);
        return *this;
    }

    auto pack_bytes(std::span<byte const> input) -> packer & {
        auto const bytes = encode_bytes(input);
        append_buffer(bytes);
        return *this;
    }

    auto pack_bytes(bytes_view_t input) -> packer & {
        auto const bytes = encode_bytes(input);
        append_buffer(bytes);
        return *this;
    }

    auto pack_list(std::vector<std::string_view> const & input) -> packer & {
        std::vector<bytes_t> bytes;
        bytes.reserve(input.size());
        for (auto const & item : input) {
            bytes.push_back(encode_bytes(std::span{ reinterpret_cast<byte const *>(item.data()), item.size() }));
        }

        append_buffer(encode_list(bytes));
        return *this;
    }

    auto pack_list(std::vector<std::span<byte const>> const & input) -> packer & {
        std::vector<bytes_t> bytes;
        bytes.reserve(input.size());
        for (auto const & item : input) {
            bytes.push_back(encode_bytes(item));
        }

        append_buffer(encode_list(bytes));
        return *this;
    }

    auto pack_list(std::vector<bytes_view_t> const & input) -> packer & {
        std::vector<bytes_t> bytes;
        bytes.reserve(input.size());
        for (auto const & item : input) {
            bytes.push_back(encode_bytes(item));
        }

        append_buffer(encode_list(bytes));
        return *this;
    }

    template <typename T> requires is_serializable<T, packer>
    auto pack(T const & object) -> packer & {
        object.serialize(*this);
        pack_list();
        return *this;
    }

private:
    auto encode_length(uint64_t length, uint32_t offset) -> bytes_be_t {
        if (length < 56) {
            return bytes_be_t{ static_cast<byte>(length + offset) };
        } else if (length < std::numeric_limits<uint64_t>::max()) {
            auto be_length = convert_to<bytes_be_t>::from(length).value();
            return static_cast<byte>(be_length.size() + offset + 55) + be_length;
        }

        unreachable();
    }

    auto encode_bytes(std::span<byte const> input) -> bytes_t {
        if (input.size() == 1 && input[0] < 0x80) {
            return bytes_t { input[0] };
        }

        return encode_length(input.size(), 0x80).template to<byte_numbering::none>() + input;
    }

    auto encode_bytes(bytes_view_t input) -> bytes_t {
        if (input.size() == 1 && input[0] < 0x80) {
            return bytes_t { input[0] };
        }

        return encode_length(input.size(), 0x80).template to<byte_numbering::none>() + input;
    }

    auto encode_list(std::vector<bytes_t> const & input) -> bytes_t {
        bytes_t output;
        for (auto const & item : input) {
            output += encode_bytes(item);
        }

        return encode_length(static_cast<uint64_t>(output.size()), 0xc0).template to<byte_numbering::none>() + output;
    }

    auto encode_list() -> bytes_t {
        return encode_length(stream_.size(), 0xc0).template to<byte_numbering::none>() + stream_.bytes();
    }

    template <std::integral T>
    auto pack_integer_impl(T d) -> void {
        auto const bytes = convert_to<bytes_be_t>::from(d).transform([](auto && bytes_be) { return bytes_be.template to<byte_numbering::none>(); }).value();
        append_buffer(encode_bytes(bytes));
    }

    auto append_buffer(std::span<byte const> input) -> void {
        stream_.append(input);
    }
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_PACK
