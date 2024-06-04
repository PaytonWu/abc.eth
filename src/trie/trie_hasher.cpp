// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/trie/trie_hasher.h>

#include <abc/ethereum/trie/compact_bytes.h>
#include <abc/ethereum/trie/full_node.h>
#include <abc/ethereum/trie/hash_node.h>
#include <abc/ethereum/trie/short_node.h>

#include <cassert>

namespace abc::ethereum::trie
{

auto
trie_hasher::hash(std::shared_ptr<node_face> const & node, bool force) -> std::pair<h256_t, std::shared_ptr<node_face>>
{
    assert(node);

    if (!node->cache().hash().empty())
    {
        return {node->cache().hash(), node};
    }

    switch (node->type())
    {
        case node_type::short_node:
        {
            auto short_node = std::static_pointer_cast<trie::short_node>(node);
            assert(short_node);
            auto [collapsed, cached] = this->hash_short(short_node.get(), force);

            break;
        }

        case node_type::full_node:
        {
            break;
        }

        default:
        {
            break;
        }
    }
}

auto
trie_hasher::hash_short(trie::short_node * short_node, bool force) -> std::pair<std::shared_ptr<node_face>, std::shared_ptr<node_face>>
{
    assert(short_node);

    auto collapsed = std::make_shared<trie::short_node>(compact_bytes{short_node->nibble_keys()}, short_node->value(), short_node->cache());
    auto cached = short_node->clone();

    auto const & value_node = short_node->value();
    assert(value_node);
    if (value_node->type() == node_type::short_node || value_node->type() == node_type::full_node)
    {
        auto [hash, node] = this->hash(value_node, false);
        collapsed->value(std::make_shared<trie::hash_node>(hash));
        cached->value(std::move(node));
    }

    return { collapsed, cached };
}

auto
trie_hasher::short_node_hash(trie::short_node * short_node, bool force)
{

}

}
