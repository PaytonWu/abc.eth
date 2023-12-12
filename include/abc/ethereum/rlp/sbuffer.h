// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_SBUFFER
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_SBUFFER

#pragma once

#include "sbuffer_decl_fwd.h"

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
    auto bytes_view() const noexcept -> bytes_view_t;
    auto clear() noexcept -> void;
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_SBUFFER
