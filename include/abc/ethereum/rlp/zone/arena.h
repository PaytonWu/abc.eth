// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ZONE_ARENA
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ZONE_ARENA

#pragma once

#include "allocator.h"
#include "arena_decl.h"
#include "constructor.h"

#include <abc/byte.h>
#include <abc/memory.h>

#include <cstddef>
#include <vector>

namespace abc::ethereum::rlp::zone {

template <typename AllocatorT>
class arena {
private:
    AllocatorT allocator_;
    std::vector<finalizer> finalizers_;

public:
    arena(arena const&) = delete;
    auto operator=(arena const&) -> arena & = delete;
    arena(arena &&) = default;
    auto operator=(arena &&) -> arena & = default;
    ~arena() = default;

    explicit arena(std::size_t chunk_size = ABC_RLP_ARENA_CHUNK_SIZE) : allocator_{ chunk_size } {
    }

    template <std::size_t Alignment>
    [[nodiscard]]
    auto allocate_align(std::size_t size) -> byte * {
        return allocator_.template allocate<aligned, Alignment>(size);
    }

    template <typename T, std::size_t Alignment = alignof(T)>
    [[nodiscard]]
    auto allocate_align() -> byte * {
        return allocate_align<Alignment>(sizeof(T));
    }

    [[nodiscard]] auto allocate_align(std::size_t size, std::size_t alignment = ABC_RLP_ARENA_ALIGNMENT) -> byte * {
        return allocator_.template allocate<aligned>(size, alignment);
    }

    template <typename T, typename ... ArgsT>
    [[nodiscard]]
    auto construct(ArgsT &&... args) -> T * {
        auto * ptr = allocate_align<T>();
        try {
            finalizers_.push_back({ constructor<T>::default_destructor, ptr });
        } catch (...) {
            deallocate<T>();
            throw;
        }

        try {
            construct<T>(ptr, std::forward<ArgsT>(args)...);
        } catch (...) {
            finalizers_.pop_back();
            deallocate<T>();
            throw;
        }
    }

private:
    template <typename T>
    auto deallocate() -> void {
        allocator_.template deallocate(sizeof(T));
    }

    auto deallocate(std::size_t size) -> void {
        allocator_.template deallocate(size);
    }
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ZONE_ARENA
