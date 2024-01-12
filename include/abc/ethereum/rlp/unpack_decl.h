// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_UNPACK_DECL
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_UNPACK_DECL

#pragma once

#include "object_decl.h"

#include <cstddef>
#include <stack>

namespace abc::ethereum::rlp {

namespace details {

class unpack_list_stack
{
private:
    zone::arena<zone::allocator> * arena_{ nullptr };
    std::vector<object> list_items_{};

public:
    unpack_list_stack(unpack_list_stack const &) = delete;
    unpack_list_stack(unpack_list_stack &&) = default;

    auto
    operator=(unpack_list_stack const &) -> unpack_list_stack & = delete;

    auto
    operator=(unpack_list_stack &&) -> unpack_list_stack & = default;

    ~unpack_list_stack() = default;

    explicit unpack_list_stack(zone::arena<zone::allocator> *);

    auto
    push(object const & obj) -> void;

    auto
    result() -> expected<object, std::error_code>;
};

struct [[nodiscard]] decoded_raw
{
    std::size_t offset{ 0 };
    std::size_t length{ 0 };
    type object_type{ type::invalid };
};

class context
{
private:
    zone::arena<zone::allocator> * arena_{ nullptr };
    object data_{};
    std::stack<unpack_list_stack> stack_{};

public:
    explicit context(zone::arena<zone::allocator> * arena);

    /// @brief Parse the RLP encoded data from the given offset.
    /// @param data The RLP encoded data.
    /// @param offset The offset to start parsing and the offset will be updated to the end of the parsed data.
    /// @return > 0: extra data left. < 0: Error. = 0: no extra data, fully parsed.
    auto
    execute(bytes_view_t data, std::size_t & offset) -> int;

    auto
    data() const noexcept -> object const &;

private:
    static auto
    to_integer(bytes_be_view_t bytes) -> expected<std::uint64_t, std::error_code>;

    static auto
    decode_raw(bytes_view_t input, std::size_t & offset) -> expected<decoded_raw, std::error_code>;

    auto
    decode_list(bytes_view_t input, std::size_t & offset) -> expected<object, std::error_code>;

    auto
    decode_single(bytes_view_t input, std::size_t & offset) -> expected<object, std::error_code>;
};

}

using unpack_reference_func = auto (*)(void const * ptr, std::size_t size) -> bool;

inline constexpr std::size_t COUNTER_SIZE = sizeof(unsigned int);

inline constexpr std::size_t RLP_UNPACKER_INIT_BUFFER_SIZE{64*1024};
inline constexpr std::size_t RLP_UNPACKER_RESERVE_SIZE{32*1024};

auto
unpack(bytes_view_t const & bytes) -> expected<object_handle, std::error_code>;

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_UNPACK_DECL
