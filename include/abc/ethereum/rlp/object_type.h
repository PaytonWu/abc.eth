// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_OBJECT_TYPE)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_OBJECT_TYPE

#pragma once

namespace abc::ethereum::rlp {

enum class type {
    invalid = 0,
    byte,
    bytes,
    list,
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_OBJECT_TYPE
