// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_OBJECT_TYPE)
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_OBJECT_TYPE

#pragma once

namespace abc::ethereum::rlp {

enum class type {
    bytes = 0,
    string = 1,
    list = 2,
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_OBJECT_TYPE
