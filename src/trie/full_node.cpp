// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/trie/full_node.h>
#include <abc/ethereum/trie/hash_flag.h>

namespace abc::ethereum::trie
{

auto
full_node::clone() const -> std::shared_ptr<full_node>
{
    return std::make_shared<full_node>(*this);
}

auto
full_node::cache() const -> hash_flag
{
    return flag_;
}

auto
full_node::fstring(std::string_view /*indent*/) const -> std::string
{
    return {};
}

auto
full_node::children(std::size_t index) const noexcept -> observer_ptr<node_face>
{
    return make_observer(children_[index].get());
}

auto
full_node::children(std::size_t index) noexcept -> std::shared_ptr<node_face> &
{
    return children_[index];
}

} // namespace abc::ethereum::trie
