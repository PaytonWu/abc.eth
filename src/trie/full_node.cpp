// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/trie/full_node.h>
#include <abc/ethereum/trie/node_flag.h>

namespace abc::ethereum::trie
{

auto
full_node::cache() const -> std::tuple<hash_node, bool>
{
    return {flag_.hash_node(), flag_.dirty()};
}

auto
full_node::fstring(std::string_view /*indent*/) const -> std::string
{
    return {};
}

} // namespace abc::ethereum::trie
