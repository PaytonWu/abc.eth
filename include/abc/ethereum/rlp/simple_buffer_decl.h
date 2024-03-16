// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_SIMPLE_BUFFER_DECL
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_SIMPLE_BUFFER_DECL

#pragma once

#include "simple_buffer_fwd_decl.h"

#include <abc/bytes.h>

namespace abc::ethereum::rlp
{

class simple_buffer
{
private:
    bytes_t buffer_{};

public:
    simple_buffer() = default;
    simple_buffer(simple_buffer const &) = delete;
    simple_buffer(simple_buffer &&) = default;
    ~simple_buffer() = default;

    auto
    operator=(simple_buffer const &) -> simple_buffer & = delete;

    auto
    operator=(simple_buffer &&) -> simple_buffer & = default;

    auto
    append(bytes_view_t bytes) -> void;

    auto
    clear() noexcept -> void;

    template <byte_numbering ByteNumbering = byte_numbering::none>
    auto
    bytes_view() const noexcept -> bytes_view<ByteNumbering>;

    [[nodiscard]] auto
    size() const noexcept -> std::size_t;
};

} // namespace abc::ethereum::rlp

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_SIMPLE_BUFFER_DECL
