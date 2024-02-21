// Copyright(c) 2024 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/rlp/error.h>
#include <abc/ethereum/types/address.h>
#include <abc/ethereum/types/rlp/address.h>

namespace abc::ethereum::rlp::adaptor
{

auto
as<types::address>::operator()(rlp::object const & o) const -> types::address
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

auto
convert<types::address>::operator()(rlp::object const & o, types::address & v) const -> rlp::object const &
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

} // namespace abc::ethereum::rlp::adaptor
