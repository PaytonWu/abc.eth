// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/rlp/object.h>

namespace abc::ethereum::rlp {

object_handle::object_handle(object const & obj, std::unique_ptr<zone::arena<zone::allocator>> arena) noexcept
    : object_{ obj }, arena_{ std::move(arena) }
{
}

auto
object_handle::get() const noexcept -> const object &
{
    return object_;
}

auto
object_handle::operator*() const noexcept -> const object &
{
    return object_;
}

auto
object_handle::operator->() const noexcept -> const object *
{
    return &object_;
}

auto
object_handle::arena() noexcept -> zone::arena <zone::allocator> &
{
    return *arena_;
}

auto
object_handle::arena() const noexcept -> zone::arena<zone::allocator> const &
{
    return *arena_;
}

}