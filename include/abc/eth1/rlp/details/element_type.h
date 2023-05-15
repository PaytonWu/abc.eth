// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(ABC_ETH1_RLP_DETAILS_ELEMENT_TYPE)
#define ABC_ETH1_RLP_DETAILS_ELEMENT_TYPE

#pragma once

#include <cstdint>

namespace abc::eth1::rlp::details {

enum class xabc_element_type : uint8_t {
    byte = 0,
    bytes = 1,
    list = 2,
};

#endif //ABC_ETH1_RLP_DETAILS_ELEMENT_TYPE
