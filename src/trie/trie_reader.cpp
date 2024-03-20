// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/trie/trie_reader.h>
#include <abc/ethereum/trie/error.h>

namespace abc::ethereum::trie
{

auto
trie_reader::node(nibble_bytes_view path, h256_t const & hash) const -> expected<bytes_t, std::error_code>
{
    assert(reader_);
    auto result = reader_->node(owner_, hash, path).transform_error([](auto &&) { return make_error_code(errc::missing_node); });
    if (result.is_err())
    {
        return result;
    }

    if (result.value().empty())
    {
        return make_unexpected(make_error_code(errc::missing_node));
    }

    return result;
}

}
