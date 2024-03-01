// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/trie/node_face.h>

namespace abc::ethereum::trie
{

auto
node_face::type() const noexcept -> node_type
{
    return node_type::invalid;
}

} // namespace abc::ethereum::trie
