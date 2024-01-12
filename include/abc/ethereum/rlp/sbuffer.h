// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_SBUFFER
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_SBUFFER

#pragma once

#include "sbuffer_fwd_decl.h"

#include <abc/bytes.h>

namespace abc::ethereum::rlp {

class sbuffer {
private:
    bytes_t buffer_{};

public:
    sbuffer() = default;
    sbuffer(sbuffer const &) = delete;
    auto operator=(sbuffer const &) -> sbuffer & = delete;
    sbuffer(sbuffer &&) = default;
    auto operator=(sbuffer &&) -> sbuffer & = default;
    ~sbuffer() = default;

    auto append(bytes_view_t bytes) -> void;
    auto clear() noexcept -> void;

    template <byte_numbering ByteNumbering = byte_numbering::none>
    auto bytes_view() const noexcept -> bytes_view<ByteNumbering>
    {
        return abc::bytes_view<ByteNumbering>{ bytes_view_t{ buffer_ } };
    }
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_SBUFFER
