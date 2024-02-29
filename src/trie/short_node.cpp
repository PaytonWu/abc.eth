// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/trie/hash_flag.h>
#include <abc/ethereum/trie/short_node.h>

namespace abc::ethereum::trie
{

auto
short_node::cache() const -> hash_flag
{
    return flag_;
}

auto
short_node::fstring(std::string_view /*indent*/) const -> std::string
{
    return {};
}

} // namespace abc::ethereum::trie
