// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/rlp/unpack.h>

#include <cassert>


namespace abc::ethereum::rlp::details {

auto to_integer(bytes_be_view_t bytes) -> expected<std::uint64_t, std::error_code>;

auto decode_raw(bytes_view_t input, std::size_t & offset) -> expected<decoded_raw, std::error_code> {
    if (offset >= input.size()) {
        return make_unexpected(make_error_code(errc::empty_input));
    }

    decoded_raw raw_item;

    std::size_t const length = input.size() - offset;
    std::size_t const selector = input[offset];

    do {
        if (selector <= 0x7F) {
            raw_item.offset = offset;
            raw_item.length = 1;
            raw_item.object_type = type::bytes;

            break;
        }

        if (selector <= 0xB7 and length > selector - 0x80) {
            raw_item.offset = offset + 1;
            raw_item.length = static_cast<std::size_t>(selector - 0x80);
            raw_item.object_type = type::bytes;

            break;
        }

        if (selector <= 0xBF and length > selector - 0xB7) {
            std::size_t const length_of_length = selector - 0xB7;
            std::size_t const length_of_bytes = static_cast<std::size_t>(to_integer(bytes_be_view_t::from(input.subview(offset + 1, length_of_length))).value());

            if (length > length_of_length + length_of_bytes) {
                raw_item.offset = offset + 1 + length_of_length;
                raw_item.length = length_of_bytes;
                raw_item.object_type = type::bytes;

                break;
            }
        }

        if (selector <= 0xF7 and length > selector - 0xC0) {
            raw_item.offset = offset + 1;
            raw_item.length = static_cast<std::size_t>(selector - 0xC0);
            raw_item.object_type = type::list;

            break;
        }

        assert(selector <= 0xFF);
        if (length > selector - 0xF7) {
            std::size_t const length_of_length = selector - 0xF7;
            std::size_t const length_of_bytes = to_integer(bytes_be_view_t::from(input.subview(offset + 1, selector - 0xF7))).value();

            if (length > length_of_length + length_of_bytes) {
                raw_item.offset = offset + 1 + length_of_length;
                raw_item.length = length_of_bytes;
                raw_item.object_type = type::list;

                break;
            }
        }

        return make_unexpected(make_error_code(errc::invalid_encoded_data));
    } while (false);

    offset = raw_item.offset + raw_item.length;
    return raw_item;
}

auto decode_list(bytes_view_t input, size_t & offset) -> expected<object, std::error_code>;

auto decode_single(bytes_view_t input, std::size_t & offset) -> expected<object, std::error_code> {
    if (input.empty() || offset >= input.size()) {
        return make_unexpected(make_error_code(errc::empty_input));
    }

    return decode_raw(input, offset).transform([input](auto const & decoded_item) {
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
                o = decode_list(view, sub_offset).value_or(object{ rlp::type::list });

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

