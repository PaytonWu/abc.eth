// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_CONCEPTS
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_CONCEPTS

#pragma once

#include <abc/bytes.h>

#include <concepts>
#include <string_view>

namespace abc::ethereum::rlp {

template <typename T>
concept is_packer = requires(T t) {
    { t.pack_integer(0) } -> std::same_as<T &>;
    { t.pack_string("") } -> std::same_as<T &>;
    { t.pack_bytes(bytes_view_t{}) } -> std::same_as<T &>;
    { t.pack_string(std::string_view{}) } -> std::same_as<T &>;
    { t.pack_list(std::vector<bytes_view_t>{}) } -> std::same_as<T &>;
};

template <typename T, typename PackerT>
concept is_serializable = requires(T const t, PackerT & packer) {
    { t.serialize(packer) } -> std::same_as<PackerT &>;
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_CONCEPTS
