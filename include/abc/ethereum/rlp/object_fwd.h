// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_OBJECT_FWD
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_OBJECT_FWD

#pragma once
#include "object_fwd_decl.h"
#include "object_type.h"

#include <abc/bytes.h>
#include <abc/bytes_view.h>

#include <cstdint>
#include <memory>
#include <string_view>
#include <variant>
#include <vector>

namespace abc::ethereum::rlp {

struct object_array {
    std::size_t size{ 0 };
    object const * ptr{ nullptr };
};

struct object_bytes {
    std::size_t size{ 0 };
    byte const * ptr{ nullptr };
};

struct object {
    union {
        object_array array{};
        object_bytes bytes;
    } data;
    type type{ type::invalid };

    object() = default;
    constexpr object(rlp::type t) : type{ t } {
    }
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_OBJECT_FWD
