// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/rlp/unpack.h>

#include <cassert>

namespace abc::ethereum::rlp {

namespace details {

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

auto decode(bytes_view_t input, std::size_t & offset, object & result) -> expected<object, std::error_code> {
    auto decoded_item = decode_length(input).transform([input, &offset](auto const & decoded_item) -> object {
        object o;

        switch (decoded_item.object_type) {
            case type::bytes: {
                auto const bytes_view = input.subview(decoded_item.offset, decoded_item.length);
                o.data = bytes_t::from(bytes_view);
                offset = decoded_item.offset + decoded_item.length;
                break;
            }

            case type::list: {
                auto const bytes_view = input.subview(decoded_item.offset, decoded_item.length);
                o.data = decoded_item.length;
                break;
            }

            default:
                break;
        }

        return o;
    });
}

auto decode_list(bytes_view_t input) -> expected<object, std::error_code> {
    auto const length = input.size();
    std::size_t offset = 0;

    object o;
    o.type = type::list;


}

//auto context::execute(abc::bytes_view_t data, std::size_t & offset) -> int {
//    assert(data.size() >= offset);
//
//    start_ = data.data();
//    current_ = start_ + offset;
//
//    byte const * const end = start_ + data.size();
//    byte const * n = nullptr;
//
//    object obj;
//
//    if (current_ == end) {
//        offset = static_cast<std::size_t>(current_ - start_);
//        return 0;
//    }
//
//    byte selector = current_[0];
//    if (selector <= 0x7F) {
//        return decoded_item{ 0, 1, type::bytes };
//    }
//
//    if (selector <= 0xB7 and length > selector - 0x80) {
//        return decoded_item{ .offset = 1, .length = static_cast<std::size_t>(selector - 0x80), .object_type = type::bytes};
//    }
//
//    if (selector <= 0xBF and length > selector - 0xB7 and length > selector - 0xB7 + to_integer(bytes_be_view_t::from(input.subview(1, selector - 0xB7))).value()) {
//        std::size_t const length_of_bytes_length = selector - 0xB7;
//        std::size_t const bytes_length = static_cast<std::size_t>(to_integer(bytes_be_view_t::from(input.subview(1, length_of_bytes_length))).value());
//
//        return decoded_item{ .offset = 1 + length_of_bytes_length, .length = bytes_length, .object_type = type::bytes };
//    }
//
//    if (selector <= 0xF7 and length > selector - 0xC0) {
//        return decoded_item{ .offset = 1, .length = static_cast<std::size_t>(selector - 0xC0), .object_type = type::list };
//    }
//
//    if (selector <= 0xFF and length > selector - 0xF7 and length > selector - 0xF7 + to_integer(bytes_be_view_t::from(input.subview(1, selector - 0xF7))).value()) {
//        std::size_t const length_of_list_length = selector - 0xF7;
//        std::size_t const list_length = static_cast<std::size_t>(to_integer(bytes_be_view_t::from(input.subview(1, length_of_list_length))).value());
//
//        return decoded_item{ .offset = 1 + length_of_list_length, .length = list_length, .object_type = type::list };
//    }
//}

}

}