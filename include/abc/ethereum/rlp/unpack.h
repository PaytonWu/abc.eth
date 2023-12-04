// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_UNPACK)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_UNPACK

#pragma once

#include "error.h"
#include "object_fwd.h"
#include "object_type.h"
#include "unpack_decl.h"
#include "zone/allocator.h"
#include "zone/arena.h"

#include <abc/byte.h>
#include <abc/bytes_view.h>
#include <abc/expected.h>

#include <cstddef>
#include <cstdint>
#include <concepts>
#include <system_error>
#include <stack>

namespace abc::ethereum::rlp::details {

class unpack_user {

};

class unpack_list_stack {
private:
    zone::arena<zone::allocator> arena_{};
    std::vector<object> list_items_{};

public:
    unpack_list_stack() = default;
    unpack_list_stack(unpack_list_stack const &) = delete;
    auto operator=(unpack_list_stack const &) -> unpack_list_stack & = delete;
    unpack_list_stack(unpack_list_stack &&) = default;
    auto operator=(unpack_list_stack &&) -> unpack_list_stack & = default;
    ~unpack_list_stack() = default;

    auto push(object const & obj) -> void;
    auto result() -> expected<object, std::error_code>;
};

struct [[nodiscard]] decoded_raw {
    std::size_t offset{ 0 };
    std::size_t length{ 0 };
    type object_type{ type::invalid };
};

class context {
private:
    zone::arena<zone::allocator> arena_;
    object data_;
    std::stack<unpack_list_stack> stack_;

public:
    auto execute(bytes_view_t data, std::size_t & offset) -> int;

private:
    static auto to_integer(bytes_be_view_t bytes) -> expected<std::uint64_t, std::error_code>;
    static auto decode_raw(bytes_view_t input, std::size_t & offset) -> expected<decoded_raw, std::error_code>;

    auto decode_list(bytes_view_t input, std::size_t & offset) -> expected<object, std::error_code>;
    auto decode_single(bytes_view_t input, std::size_t & offset) -> expected<object, std::error_code>;
};

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
