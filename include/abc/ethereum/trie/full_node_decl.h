// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_FULL_NODE
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_FULL_NODE

#pragma once

#include "full_node_fwd_decl.h"
#include "node_face_fwd_decl.h"
#include "node_flag_decl.h"

#include <array>
#include <memory>

namespace abc::ethereum::trie
{

class full_node
{
    std::array<std::shared_ptr<node_face>, 17> children_;
    node_flag flag_;
};

}

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TRIE_FULL_NODE
