// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/rlp/unpack.h>

#include <abc/ethereum/rlp/error.h>
#include <abc/converter.h>

namespace abc::ethereum::rlp {

auto to_integer(bytes_be_view_t bytes) -> expected<std::uint64_t, std::error_code> {
    auto const length = bytes.size();

    if (length == 0) {
        return make_unexpected(make_error_code(errc::empty_input));
    }

    return convert_to<std::uint64_t>::from(bytes);
}

}