// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "abc/ethereum/trie/hash_node.h"
#include <abc/ethereum/rlp/error.h>
#include <abc/ethereum/rlp/raw.h>
#include <abc/ethereum/trie/compact_bytes.h>
#include <abc/ethereum/trie/error.h>
#include <abc/ethereum/trie/nibble_bytes.h>
#include <abc/ethereum/trie/node_decode.h>
#include <abc/ethereum/trie/value_node.h>

namespace abc::ethereum::trie
{

auto
decode_ref(bytes_view_t buf) -> expected<std::pair<std::shared_ptr<node_face>, bytes_view_t>, std::error_code>
{
    return rlp::split(buf).and_then([buf](auto && decoded_item) -> expected<std::pair<std::shared_ptr<node_face>, bytes_view_t>, std::error_code> {
        switch (decoded_item.type)
        {
            case rlp::type::list:
            {
                if (auto const size = buf.size() - decoded_item.rest.size(); size > h256_t{}.size())
                {
                    return make_unexpected(make_error_code(errc::over_sized_embedded_node));
                }

                return decode_node_unsafe(h256_t{}, buf).transform([&decoded_item](auto && node) -> std::pair<std::shared_ptr<node_face>, bytes_view_t> {
                    return std::make_pair(static_cast<std::shared_ptr<trie::node_face>>(node), decoded_item.rest);
                });
            }

            case rlp::type::bytes:
            {
                if (decoded_item.content.empty())
                {
                    return std::make_pair(nullptr, decoded_item.rest);
                }

                if (decoded_item.content.size() == h256_t{}.size())
                {
                    return std::make_pair(static_cast<std::shared_ptr<trie::node_face>>(std::make_shared<trie::hash_node>(h256_t::from(decoded_item.content))), decoded_item.rest);
                }

                [[fallthrough]];
            }

            case rlp::type::byte:
                [[fallthrough]];
            default:
            {
                return make_unexpected(make_error_code(rlp::errc::non_canonical_size));
            }
        }
    });
}

auto
decode_short_node(h256_t const & hash, bytes_view_t encoded_data) -> expected<std::shared_ptr<short_node>, std::error_code>
{
    return rlp::split_bytes(encoded_data).and_then([&hash](auto && decoded_item) {
        hash_flag hf{hash};
        auto key = nibble_bytes{compact_bytes{decoded_item.content}};
        if (key.has_terminator())
        {
            return rlp::split_bytes(decoded_item.rest).transform([&key, &hf](auto && value_item) {
                return std::make_shared<trie::short_node>(key, std::make_shared<trie::value_node>(value_item.content), hf);
            });
        }
        return decode_ref(decoded_item.rest).transform([&key, &hf](auto && value) { return std::make_shared<trie::short_node>(key, value.first, hf); });
    });
}

auto
decode_full_node(h256_t const & hash, bytes_view_t encoded_data) -> expected<std::shared_ptr<full_node>, std::error_code>
{
    auto full_node = std::make_shared<trie::full_node>(hash);
    for (auto i = 0u; i < 16; ++i)
    {
        auto result = decode_ref(encoded_data).transform([&full_node, i, &encoded_data](auto && decoded_item) {
            full_node->children(i) = decoded_item.first;
            encoded_data = decoded_item.second;
        });
        if (result.is_err())
        {
            return make_unexpected(result.error());
        }
    }

    auto result = rlp::split_bytes(encoded_data).transform([&full_node](auto && decoded_item) {
        if (!decoded_item.content.empty())
        {
            full_node->children(16) = std::make_shared<trie::value_node>(decoded_item.content);
        }
    });
    if (result.is_err())
    {
        return make_unexpected(result.error());
    }

    return full_node;
}

auto
decode_node_unsafe(h256_t const & hash, bytes_view_t data) -> expected<std::shared_ptr<node_face>, std::error_code>
{
    if (data.empty())
    {
        return make_unexpected(make_error_code(errc::unexpected_eof));
    }

    rlp::split_list(data).transform([](auto && decoded_item) {
        rlp::count_value(decoded_item.content).transform([](std::uint64_t const count) {
            switch (count)
            {
                case 2:
                {
                    break;
                }
                case 17:
                {
                    // branch node
                    break;
                }
                default:
                {
                    return make_unexpected(make_error_code(errc::invalid_node));
                }
            }
        }
    });
    return std::make_shared<node_face>(hash, data);
}

} // namespace abc::ethereum::trie
