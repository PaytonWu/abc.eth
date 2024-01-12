// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_PARSE_RESULT
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_PARSE_RESULT

#pragma once

namespace abc::ethereum::rlp
{

enum class parse_result
{
    parse_success =  2,
    parse_extra_bytes =  1,
    parse_continue =  0,
    parse_error = -1
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_PARSE_RESULT
