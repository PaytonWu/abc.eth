// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/trie/full_node.h>
#include <abc/ethereum/trie/hash_flag.h>

#include <range/v3/view/transform.hpp>
#include <range/v3/algorithm/copy.hpp>

namespace abc::ethereum::trie
{

full_node::full_node(h256_t const & hash) : flag_{hash}
{
}

auto
full_node::clone() const -> std::shared_ptr<full_node>
{
    auto cloned = std::make_shared_for_overwrite<full_node>();
    *cloned = *this;
    return cloned;
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
full_node::child(std::size_t index) const noexcept -> observer_ptr<node_face>
{
    return make_observer(children_[index].get());
}

auto
full_node::child(std::size_t index) noexcept -> std::shared_ptr<node_face> &
{
    return children_[index];
}

auto
full_node::children() const noexcept -> std::vector<observer_ptr<node_face>>
{
    std::vector<observer_ptr<node_face>> result;
    result.reserve(children_size);

    ranges::copy(children_ | ranges::views::transform([](auto & child) { return make_observer(child.get()); }), std::back_inserter(result));
    return result;
}

auto
full_node::reset_hash_flag() -> void
{
    flag_.reset();
}

} // namespace abc::ethereum::trie
