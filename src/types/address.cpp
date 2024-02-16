// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "abc/ethereum/types/address.h"
#include "abc/bytes.h"
#include "abc/ethereum/crypto/keccak.h"
#include "abc/ethereum/types/error.h"

#include <range/v3/algorithm/copy.hpp>

#include <memory>

using namespace CryptoPP;

namespace abc::ethereum::types
{

address::address(crypto::secp256k1::public_key const & public_key)
{
    auto const & bytes = public_key.bytes();
    auto const & hash_result = bytes.subspan(1).transform([](auto && bytes) { return ethereum::crypto::keccak256_t::digest(bytes); });
    assert(hash_result.is_ok());
    auto const & hash = hash_result.value();
    //    [[maybe_unused]] auto const _ = hash_result.and_then([](auto && bytes) { return bytes.subspan(12); })
    //        .transform([this](auto && span) { ranges::copy(span, std::begin(raw_address_)); });

    ranges::copy(hash.subspan(12).value(), std::begin(raw_address_));
}

address::address(abc::hex_string const & hex_string) noexcept : raw_address_{value_type::from<byte_numbering::msb0>(hex_string.bytes<byte_numbering::msb0>()).value()}
{
    assert(hex_string.bytes_size() == length);
}

address::address(value_type const & address_bytes) noexcept : raw_address_{address_bytes}
{
}

auto
address::from(crypto::secp256k1::public_key const & public_key) -> address
{
    return address{public_key};
}

auto
address::from(crypto::secp256k1::private_key const & private_key) -> expected<address, std::error_code>
{
    return private_key.public_key().transform([](auto && pubkey) { return address::from(pubkey); });
}

auto
address::from(abc::hex_string const & hex_string) -> expected<address, std::error_code>
{
    if (hex_string.bytes_size() != length)
    {
        return make_unexpected(errc::invalid_address);
    }

    return address{hex_string};
}

auto
address::from(value_type address_bytes) -> address
{
    return address{std::move(address_bytes)};
}

auto
address::from(std::string_view hex_string) -> expected<address, std::error_code>
{
    return hex_string::from(hex_string).and_then([](auto && hex_str) { return address::from(hex_str); });
}

auto
address::from(bytes_be_view_t const bytes) -> expected<address, std::error_code>
{
    return value_type::from(bytes).transform([](auto && bytes) { return address::from(bytes); });
}

} // namespace abc::ethereum::types
