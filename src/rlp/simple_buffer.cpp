// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include "abc/ethereum/rlp/simple_buffer.h"

namespace abc::ethereum::rlp
{

auto
simple_buffer::append(bytes_view_t bytes) -> void
{
    buffer_ += bytes;
}

auto
simple_buffer::clear() noexcept -> void
{
    buffer_.clear();
}

} // namespace abc::ethereum::rlp
