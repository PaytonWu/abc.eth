// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_ADDRESS
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_ADDRESS

#pragma once

#include "address_fwd_decl.h"

#include <abc/byte.h>
#include <abc/ethereum/crypto/secp256k1.h>
#include <abc/expected.h>
#include <abc/fixed_bytes.h>
#include <abc/hex_string.h>

#include <array>
#include <span>

namespace abc::ethereum::types
{

class [[nodiscard]] address
{
public:
    static constexpr size_t length = 20;
    using value_type = fixed_bytes<length, byte_numbering::msb0>;

private:
    fixed_bytes<length, byte_numbering::msb0> raw_address_{};

private:
    explicit address(crypto::secp256k1::public_key const & public_key);
    explicit address(hex_string const & hex_string) noexcept;
    explicit address(value_type const & address_bytes) noexcept;

public:
    constexpr address() = default;

    static auto
    from(crypto::secp256k1::public_key const & public_key) -> address;

    static auto
    from(crypto::secp256k1::private_key const & private_key) -> expected<address, std::error_code>;

    static auto
    from(hex_string const & hex_string) -> expected<address, std::error_code>;

    static auto
    from(std::string_view hex_string) -> expected<address, std::error_code>;

    static auto
    from(value_type address_bytes) -> address;

    static auto
    from(bytes_be_view_t bytes) -> expected<address, std::error_code>;

    [[nodiscard]] constexpr auto
    bytes() const noexcept -> value_type const &
    {
        return raw_address_;
    }

    constexpr auto
    hex_string() const -> hex_string
    {
        return abc::hex_string::from<byte_numbering::msb0>(raw_address_);
    }

    static constexpr auto
    zero() -> address const &
    {
        static constexpr address zero_address{};
        return zero_address;
    }

    constexpr friend auto
    operator==(address const & lhs, address const & rhs) noexcept -> bool = default;

    constexpr friend auto
    operator<=>(address const & lhs, address const & rhs) noexcept -> std::strong_ordering = default;
};

} // namespace abc::ethereum::types

#include <abc/ethereum/rlp/adaptor/adaptor_base.h>
#include <abc/ethereum/rlp/adaptor/as_fwd_decl.h>
#include <abc/ethereum/rlp/concepts.h>
#include <abc/ethereum/rlp/error.h>
#include <abc/ethereum/rlp/pack.h>
#include <abc/ethereum/types/address.h>

namespace abc::ethereum::rlp::adaptor
{

template <>
struct as<types::address>
{
    auto
    operator()(rlp::object const & o) const -> types::address
    {
        if (o.type != rlp::type::bytes)
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::type_error));
        }

        auto r = types::address::from(bytes_be_view_t::from(bytes_view_t{o.data.bytes.ptr, o.data.bytes.size}));
        if (!r.has_value())
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::unpack_error));
        }
        return r.value();
    }
};

template <>
struct convert<types::address>
{
    auto
    operator()(rlp::object const & o, types::address & v) const -> rlp::object const &
    {
        if (o.type != rlp::type::bytes)
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::type_error));
        }

        auto r = types::address::from(bytes_be_view_t::from(bytes_view_t{o.data.bytes.ptr, o.data.bytes.size}));
        if (!r.has_value())
        {
            abc::throw_error(make_error_code(abc::ethereum::rlp::errc::unpack_error));
        }
        v = r.value();

        return o;
    }
};

template <>
struct pack<types::address>
{
    template <packing_stream Stream>
    auto
    operator()(packer<Stream> & o, types::address const & v) const -> packer<Stream> &
    {
        o.pack_bytes(v.bytes());
        return o;
    }
};

} // namespace abc::ethereum::rlp::adaptor

#endif // ABC_ETH_INCLUDE_ABC_ETHEREUM_TYPES_ADDRESS
