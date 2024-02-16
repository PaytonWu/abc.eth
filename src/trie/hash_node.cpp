// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/trie/hash_node.h>

#include <abc/hex_string.h>

// #include <fmt/core.h>

namespace abc::ethereum::trie
{

auto
hash_node::cache() const -> std::tuple<hash_node, bool>
{
    return std::make_tuple(hash_node{}, true);
}

//auto
//hash_node::encode(rlp::sbuffer & buffer) const -> void
//{
//    buffer.append(hash_);
//}

auto
hash_node::fstring(std::string_view) const -> std::string
{
//    return fmt::format("<{}>", hex_string::from(hash_);
    return {};
}

} // namespace abc::ethereum::trie
