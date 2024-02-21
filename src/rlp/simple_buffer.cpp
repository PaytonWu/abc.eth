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
simple_buffer::append(byte const b) -> void
{
    buffer_ += b;
}

auto
simple_buffer::clear() noexcept -> void
{
    buffer_.clear();
}

auto
simple_buffer::size() const noexcept -> std::size_t
{
    return buffer_.size();
}

} // namespace abc::ethereum::rlp
