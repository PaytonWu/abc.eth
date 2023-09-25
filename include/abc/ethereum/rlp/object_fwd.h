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
    std::vector<std::unique_ptr<object>> items{};
};

struct object_bytes {
    bytes_t bytes{};
};

struct object {
    std::variant<std::monostate, object_array, object_bytes> data;

    object() = default;
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_OBJECT_FWD
