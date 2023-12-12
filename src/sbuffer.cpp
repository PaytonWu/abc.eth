// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/rlp/sbuffer.h>

namespace abc::ethereum::rlp {

auto sbuffer::append(bytes_view_t bytes) -> void {
    buffer_ += bytes;
}

auto sbuffer::bytes_view() const noexcept -> bytes_view_t {
    return buffer_;
}

auto sbuffer::clear() noexcept -> void {
    buffer_.clear();
}

}