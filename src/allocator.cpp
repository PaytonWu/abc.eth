// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <abc/ethereum/rlp/zone/allocator.h>

#include <cassert>
#include <cstring>
#include <new>

namespace abc::ethereum::rlp::zone {

allocator::allocator(std::size_t const chunk_size) : free_size_{ chunk_size } {
    assert(free_size_ > 0);

    auto * chunk_ptr = static_cast<chunk *>(std::malloc(calc_real_chunk_size(chunk_size)));
    if (chunk_ptr == nullptr) {
        throw std::bad_alloc{};
    }
    chunk_ptr->next = nullptr;
    chunk_ptr->chunk_size = chunk_size;

    header_.next = chunk_ptr;
    allocate_begin_ = reinterpret_cast<byte *>(chunk_ptr) + sizeof(chunk);
}

allocator::~allocator() noexcept {
    chunk * current = header_.next;
    while (current != nullptr) {
        chunk * next = current->next;
        std::free(current);
        current = next;
    }
    header_.next = nullptr;
    allocate_begin_ = nullptr;
    free_size_ = 0;
}

allocator::allocator(allocator && other) noexcept : header_{ other.header_ }, allocate_begin_{ other.allocate_begin_ }, free_size_{ other.free_size_ } {
    other.header_.next = nullptr;
    other.allocate_begin_ = nullptr;
    other.free_size_ = 0;
}

auto allocator::operator=(allocator && other) noexcept -> allocator & {
    if (this != &other) [[likely]] {
        this->~allocator();

        header_ = other.header_;
        allocate_begin_ = other.allocate_begin_;
        free_size_ = other.free_size_;

        other.header_.next = nullptr;
        other.allocate_begin_ = nullptr;
        other.free_size_ = 0;
    }

    return *this;
}

auto allocator::unused_size() const noexcept -> std::size_t {
    return free_size_;
}

auto allocator::used_size() const noexcept -> std::size_t {
    std::size_t used_size{ 0 };

    chunk const * current = &header_;
    while (current->next != nullptr) {
        used_size += current->chunk_size;
        current = current->next;
    }

    assert(current != nullptr);
    assert(current->chunk_size >= free_size_);

    return used_size += (current->chunk_size - free_size_);
}

void allocator::clear() noexcept {
    chunk * current = &header_;
    while (current->next != nullptr) {
        chunk * next = current->next;
        std::free(current);
        current = next;
    }
    header_.next = current;
    assert(current == nullptr);
    allocate_begin_ = reinterpret_cast<byte *>(header_.next) + sizeof(chunk);
    free_size_ = header_.next->chunk_size;
}

auto allocator::deallocate(std::size_t size) noexcept -> void {
    allocate_begin_ -= size;
    free_size_ += size;
}

auto allocator::current_chunk_size() const noexcept -> std::size_t {
    return header_.next->chunk_size;
}

auto allocator::expand(allocator & allocator, std::size_t size) -> void {
    assert(size > 0);

    auto sz = allocator.current_chunk_size();
    while (sz < size) {
        auto new_sz = sz * 2;
        if (new_sz <= sz) {
            sz = size;
            break;
        }
        sz = new_sz;
    }

    auto * new_chunk = static_cast<chunk *>(std::malloc(calc_real_chunk_size(sz)));
    if (new_chunk == nullptr) {
        throw std::bad_alloc{};
    }

    new_chunk->next = allocator.header_.next;
    new_chunk->chunk_size = sz;

    allocator.header_.next = new_chunk;
}

auto allocator::calc_real_chunk_size(std::size_t size) -> std::size_t {
    return sizeof(chunk) + size;
}

}