// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_UNPACK)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_UNPACK

#pragma once

#include "error.h"
#include "object_type.h"
#include "unpack_decl.h"
#include "object_fwd.h"

#include <abc/byte.h>
#include <abc/bytes_view.h>
#include <abc/expected.h>

#include <cstddef>
#include <cstdint>
#include <concepts>
#include <system_error>

namespace abc::ethereum::rlp {

namespace details {

class unpack_user {

};

}

struct [[nodiscard]] decoded_item {
    std::size_t offset;
    std::size_t length;
    type object_type;
};

auto to_integer(bytes_be_view_t bytes) -> expected<std::uint64_t, std::error_code>;

auto decode_length(bytes_view_t input) -> expected<decoded_item, std::error_code> {
    if (input.empty()) {
        return make_unexpected(make_error_code(errc::empty_input));
    }

    auto const length = input.size();
    auto const prefix = input[0];
    if (prefix <= 0x7F) {
        return decoded_item{ 0, 1, type::bytes };
    }

    if (prefix <= 0xB7 and length > prefix - 0x80) {
        return decoded_item{ .offset = 1, .length = static_cast<std::size_t>(prefix - 0x80), .object_type = type::bytes};
    }

    if (prefix <= 0xBF and length > prefix - 0xB7 and length > prefix - 0xB7 + to_integer(bytes_be_view_t::from(input.subview(1, prefix - 0xB7))).value()) {
        std::size_t const length_of_bytes_length = prefix - 0xB7;
        std::size_t const bytes_length = static_cast<std::size_t>(to_integer(bytes_be_view_t::from(input.subview(1, length_of_bytes_length))).value());

        return decoded_item{ .offset = 1 + length_of_bytes_length, .length = bytes_length, .object_type = type::bytes };
    }

    if (prefix <= 0xF7 and length > prefix - 0xC0) {
        return decoded_item{ .offset = 1, .length = static_cast<std::size_t>(prefix - 0xC0), .object_type = type::list };
    }

    if (prefix <= 0xFF and length > prefix - 0xF7 and length > prefix - 0xF7 + to_integer(bytes_be_view_t::from(input.subview(1, prefix - 0xF7))).value()) {
        std::size_t const length_of_list_length = prefix - 0xF7;
        std::size_t const list_length = static_cast<std::size_t>(to_integer(bytes_be_view_t::from(input.subview(1, length_of_list_length))).value());

        return decoded_item{ .offset = 1 + length_of_list_length, .length = list_length, .object_type = type::list };
    }

    return make_unexpected(make_error_code(errc::invalid_encoded_data));
}

auto decode(bytes_view_t input, bool decode_list_item, std::size_t & offset) -> expected<object, std::error_code>;
auto decode_list(bytes_view_t input, std::size_t & offset) -> expected<object, std::error_code>;


template <std::integral T>
auto unpack_integer(std::span<std::byte const> bytes) -> T {

}

namespace details {

class context {
private:
    byte const * start_;
    byte const * current_;

    std::size_t trail_;

public:
    auto execute(bytes_view_t data, std::size_t & offset) -> int;
};

}


class unpacker {
public:

    void reserve_buffer(std::size_t size = RLP_UNPACKER_RESERVE_SIZE);

    auto buffer() -> byte *;

    auto buffer_capacity() const -> std::size_t;

    void buffer_consumed(std::size_t size);

    auto message_size() const -> std::size_t;

    auto execute() -> bool;
};

}


#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_UNPACK
