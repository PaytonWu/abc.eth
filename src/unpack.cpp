// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/rlp/unpack.h>

#include <abc/ethereum/rlp/error.h>
#include <abc/converter.h>

#include <cassert>

namespace abc::ethereum::rlp::details {

auto unpack_list_stack::push(object const & obj) -> void {
    list_items_.push_back(obj);
}

auto unpack_list_stack::result() -> expected<object, std::error_code> {
    if (list_items_.empty()) {
        return make_unexpected(make_error_code(errc::empty_input));
    }

    object result;
    result.type = type::list;
    result.data.array.size = list_items_.size();
    result.data.array.ptr = reinterpret_cast<object *>(arena_.allocate_align(sizeof(object) * list_items_.size(), alignof(object)));
    std::memcpy(result.data.array.ptr, list_items_.data(), sizeof(object) * list_items_.size());

    list_items_.clear();

    return result;
}

auto context::to_integer(bytes_be_view_t bytes) -> expected<std::uint64_t, std::error_code> {
    auto const length = bytes.size();

    if (length == 0) {
        return make_unexpected(make_error_code(errc::empty_input));
    }

    if (length > sizeof(std::uint64_t)) {
        return make_unexpected(make_error_code(errc::invalid_encoded_data));
    }

    return convert_to<std::uint64_t>::from(bytes);
}

auto context::decode_raw(bytes_view_t input, std::size_t & offset) -> expected<decoded_raw, std::error_code> {
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
            std::size_t const length_of_bytes = static_cast<std::size_t>(to_integer(bytes_be_view_t::from<abc::byte_numbering::none>(input.subview(offset + 1, length_of_length))).value());

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
            std::size_t const length_of_bytes = to_integer(bytes_be_view_t::from(input.subview(offset + 1, length_of_length))).value();

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

auto context::decode_single(bytes_view_t input, std::size_t & offset) -> expected<object, std::error_code> {
    if (offset >= input.size()) {
        return make_unexpected(make_error_code(errc::empty_input));
    }

    return decode_raw(input, offset).transform([this, input](auto const & decoded_item) {
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

auto context::decode_list(bytes_view_t input, size_t & offset) -> expected<object, std::error_code> {
    if (offset >= input.size()) {
        return make_unexpected(make_error_code(errc::empty_input));
    }

    if (stack_.size() >= 1024) {
        return make_unexpected(make_error_code(errc::stack_overflow));
    }

    expected<object, std::error_code> result;

    stack_.emplace();
    while (offset < input.size()) {
        std::size_t const pre_offset = offset;

        auto item = decode_single(input, offset);
        if (!item.has_value()) {
            return make_unexpected(item.error());
        }

        auto & item_value = item.value();
        switch (item_value.type) {
            case type::bytes:
                stack_.top().push(item_value);
                break;

            case type::list: {
                auto const view = input.subview(pre_offset, offset - pre_offset);
                std::size_t sub_offset = 0;
                auto const list_item = decode_list(view, sub_offset);
                if (!list_item.has_value()) {
                    return make_unexpected(list_item.error());
                }
                stack_.top().push(list_item.value());
                break;
            }

            default:
                assert(false);
                unreachable();
        }
    }

    result = stack_.top().result();
    stack_.pop();

    return result;
}

auto context::execute(abc::bytes_view_t data, std::size_t & offset) -> int {
    return decode_single(data, offset).transform([this, data, offset](auto const & decoded_item) {
        data_ = decoded_item;
        return static_cast<int>(!!(data.size() - offset));
    }).value_or(-1);
}

}

