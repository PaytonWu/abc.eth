// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/trie/short_node.h>

#include <abc/ethereum/trie/compact_bytes.h>
#include <abc/ethereum/trie/hash_flag.h>
#include <abc/ethereum/trie/nibble_bytes.h>

#include <abc/bytes.h>

#include <cassert>

namespace abc::ethereum::trie
{

short_node::short_node(bytes_t const & raw_key, std::shared_ptr<node_face> value, hash_flag flag)
    : key_{raw_key}, value_{std::move(value)}, flag_{flag}
{
}

short_node::short_node(nibble_bytes const & nibble_key, std::shared_ptr<node_face> value, hash_flag flag)
    : key_{nibble_key}, value_{std::move(value)}, flag_{flag}
{
}

short_node::short_node(compact_bytes const & compact_key, std::shared_ptr<node_face> value, hash_flag flag)
    : key_{compact_key}, value_{std::move(value)}, flag_{flag}
{
}

auto
short_node::clone() const -> std::shared_ptr<short_node>
{
    auto cloned = std::make_shared_for_overwrite<short_node>();
    *cloned = *this;
    return cloned;
}

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

auto
short_node::raw_keys() const -> bytes_t const &
{
    assert(std::holds_alternative<bytes_t>(key_));
    return std::get<bytes_t>(key_);
}

auto
short_node::nibble_keys() const -> nibble_bytes const &
{
    assert(std::holds_alternative<nibble_bytes>(key_));
    return std::get<nibble_bytes>(key_);
}

auto
short_node::compact_keys() const -> compact_bytes const &
{
    assert(std::holds_alternative<compact_bytes>(key_));
    return std::get<compact_bytes>(key_);
}

auto
short_node::value(std::shared_ptr<node_face> v) -> void
{
    value_ = std::move(v);
}

} // namespace abc::ethereum::trie
