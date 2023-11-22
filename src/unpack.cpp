// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/rlp/unpack.h>

#include <cassert>

namespace abc::ethereum::rlp {

namespace details {

auto to_integer(bytes_be_view_t bytes) -> expected<std::uint64_t, std::error_code>;

auto decode_length(bytes_view_t input, std::size_t & offset) -> expected<decoded_item, std::error_code> {
    if (input.empty() || offset >= input.size()) {
        return make_unexpected(make_error_code(errc::empty_input));
    }

    decoded_item result;

    std::size_t const length = input.size() - offset;
    std::size_t const prefix = input[offset];

    do {
        if (prefix <= 0x7F) {
            result.offset = offset;
            result.length = 1;
            result.object_type = type::bytes;

            break;
        }

        if (prefix <= 0xB7 and length > prefix - 0x80) {
            result.offset = offset + 1;
            result.length = static_cast<std::size_t>(prefix - 0x80);
            result.object_type = type::bytes;

            break;
        }

        if (prefix <= 0xBF and length > prefix - 0xB7 and length > prefix - 0xB7 + to_integer(bytes_be_view_t::from(input.subview(offset + 1, prefix - 0xB7))).value()) {
            std::size_t const length_of_bytes_length = prefix - 0xB7;
            std::size_t const bytes_length = static_cast<std::size_t>(to_integer(bytes_be_view_t::from(input.subview(offset + 1, length_of_bytes_length))).value());

            result.offset = offset + 1 + length_of_bytes_length;
            result.length = bytes_length;
            result.object_type = type::bytes;

            break;
        }

        if (prefix <= 0xF7 and length > prefix - 0xC0) {
            result.offset = offset + 1;
            result.length = static_cast<std::size_t>(prefix - 0xC0);
            result.object_type = type::list;

            break;
        }

        if (prefix <= 0xFF and length > prefix - 0xF7 and length > prefix - 0xF7 + to_integer(bytes_be_view_t::from(input.subview(offset + 1, prefix - 0xF7))).value()) {
            std::size_t const length_of_list_length = prefix - 0xF7;
            std::size_t const list_length = static_cast<std::size_t>(to_integer(bytes_be_view_t::from(input.subview(offset + 1, length_of_list_length))).value());

            result.offset = offset + 1 + length_of_list_length;
            result.length = list_length;
            result.object_type = type::list;

            break;
        }

        return make_unexpected(make_error_code(errc::invalid_encoded_data));
    } while (false);

    offset = result.offset + result.length;
    return result;
}

auto decode_list(bytes_view_t input, size_t & offset) -> expected<object, std::error_code>;

auto decode_single(bytes_view_t input, std::size_t & offset) -> expected<object, std::error_code> {
    if (input.empty() || offset >= input.size()) {
        return make_unexpected(make_error_code(errc::empty_input));
    }

    return decode_length(input, offset).transform([input](auto const & decoded_item) {
        object o;

        o.type = decoded_item.object_type;
        switch (decoded_item.object_type) {
            case type::bytes: {
                auto const view = input.subview(decoded_item.offset, decoded_item.length);
                o.data.bytes.size = view.size();
                o.data.bytes.ptr = view.data();

                assert(o.type == type::bytes);

                break;
            }

            case type::list: {
                auto const view = input.subview(decoded_item.offset, decoded_item.length);
                std::size_t sub_offset = 0;
                o = decode_list(view, sub_offset).value_or(object{});

                assert(o.type == type::list);

                break;
            }

            default: {
                assert(false);
                unreachable();
            }
        }

        return o;
    });
}

auto decode_list(bytes_view_t input, size_t & offset) -> expected<object, std::error_code> {
    if (input.empty() || offset >= input.size()) {
        return make_unexpected(make_error_code(errc::empty_input));
    }

    std::vector<object> list;
    object result;
    result.type = type::list;

    auto item = decode_single(input, offset);
    while (item.has_value()) {
        list.push_back(item.value());

        if (offset >= input.size()) {
            break;
        }

        item = decode_single(input, offset);
    }

    result.data.array.size = list.size();
    result.data.array.ptr = list.data();

    return result;
}

}

}