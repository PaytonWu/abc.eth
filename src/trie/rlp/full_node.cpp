// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/trie/rlp/full_node.h>

#include <abc/ethereum/rlp/error.h>
#include <abc/ethereum/trie/full_node.h>

namespace abc::ethereum::rlp::adaptor
{

auto
as<trie::full_node>::operator()(rlp::object const & o) const -> trie::full_node
{
    if (o.type != rlp::type::list || o.data.array.size != trie::full_node::children_size)
    {
        abc::throw_error(make_error_code(abc::ethereum::rlp::errc::type_error));
    }

    trie::full_node result;
    for (auto i = 0uz; i < trie::full_node::children_size; ++i)
    {
        if (o.data.array.ptr[i].is_nil())
        {
            result.child(i) = nullptr;
        }
        else
        {
            // result.children(i) = as<trie::node>(o.data.array.ptr[i]);
        }
    }
    return result;
}

auto
convert<trie::full_node>::operator()(rlp::object const & o, trie::full_node & v) const -> rlp::object const &
{
    if (o.type != rlp::type::list || o.data.array.size != trie::full_node::children_size)
    {
        abc::throw_error(make_error_code(abc::ethereum::rlp::errc::type_error));
    }

    for (auto i = 0uz; i < trie::full_node::children_size; ++i)
    {
        if (o.data.array.ptr[i].is_nil())
        {
            v.child(i) = nullptr;
        }
        else
        {
            // result.children(i) = as<trie::node>(o.data.array.ptr[i]);
        }
    }

    return o;
}

} // namespace abc::ethereum::rlp::adaptor
