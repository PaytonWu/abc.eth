// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ZONE_ALLOCATOR
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ZONE_ALLOCATOR

#pragma once

#include <abc/memory.h>
#include <abc/byte.h>

#include <cstddef>

namespace abc::ethereum::rlp::zone {

enum class aligned : uint8_t {
};
enum class unaligned : uint8_t {
};

class alignment {
private:
    std::size_t value_;

public:
    constexpr
    alignment(std::size_t value) : value_{ value } {
        assert(std::has_single_bit(value_));
    }

    [[nodiscard]]
    friend constexpr
    auto operator==(alignment const & lhs, alignment const & rhs) -> bool {
        return lhs.value_ == rhs.value_;
    }

    [[nodiscard]]
    friend constexpr
    auto operator<=>(alignment const & lhs, alignment const & rhs) -> std::strong_ordering {
        return lhs.value_ <=> rhs.value_;
    }

    [[nodiscard]]
    constexpr
    operator std::size_t() const noexcept {
        return value_;
    }
};

/// @brief chunk is the basic unit of memory allocation.
// +------------------------+----------------+----------------------+
// |         next           |   chunk_size   | chunk managed memory |
// +------------------------+----------------+----------------------+
// | 8-byte on x64 platform | sizeof(size_t) |      chunk_size      |
// +------------------------+----------------+----------------------+
struct chunk {
    chunk * next{ nullptr };
    std::size_t chunk_size{ 0 };
};

class allocator {
private:
    chunk header_{};
    byte * allocate_begin_{ nullptr };
    std::size_t free_size_{ 0 };

public:
    explicit allocator(std::size_t chunk_size);

    allocator(allocator &&) noexcept;
    auto operator=(allocator &&) noexcept -> allocator &;
    allocator(allocator const &) = delete;
    auto operator=(allocator const &) = delete;

    ~allocator() noexcept;

    template <typename T, std::size_t Alignment>
    requires (std::is_same_v<aligned, T> && std::has_single_bit(Alignment))
    [[nodiscard]]
    auto
    allocate(std::size_t size) -> byte * {
        static_assert(std::has_single_bit(Alignment), "Alignment must be a power of 2");

        auto * aligned_address = address_aligned_at<Alignment>(allocate_begin_);
        auto adjusted_size = size + static_cast<std::size_t>(aligned_address - allocate_begin_);
        if (free_size_ < adjusted_size) {
            expand(*this, size + Alignment - 1);
            aligned_address = address_aligned_at<Alignment>(allocate_begin_);
            adjusted_size = size + static_cast<std::size_t>(aligned_address - allocate_begin_);
        }
        allocate_begin_ += adjusted_size;
        free_size_ -= adjusted_size;

        return aligned_address;
    }

    template <typename T>
    requires(std::is_same_v<aligned, T>)
    [[nodiscard]]
    auto
    allocate(std::size_t size, alignment alignment) -> byte * {
        assert(std::has_single_bit(static_cast<std::size_t>(alignment)));

        auto * aligned_address = address_aligned_at(alignment, allocate_begin_);
        auto adjusted_size = size + static_cast<std::size_t>(aligned_address - allocate_begin_);
        if (free_size_ < adjusted_size) {
            expand(*this, size + alignment - 1);
            aligned_address = address_aligned_at(alignment, allocate_begin_);
            adjusted_size = size + static_cast<std::size_t>(aligned_address - allocate_begin_);
        }
        allocate_begin_ += adjusted_size;
        free_size_ -= adjusted_size;

        return aligned_address;
    }

    template <typename T>
    requires(std::is_same_v<unaligned, T>)
    [[nodiscard]]
    auto
    allocate(std::size_t size) -> byte * {
        auto * unaligned_address = allocate_begin_;
        if (free_size_ < size) {
            expand(*this, size);
            unaligned_address = allocate_begin_;
        }
        allocate_begin_ += size;
        free_size_ -= size;

        return unaligned_address;
    }

    auto deallocate(std::size_t size) noexcept -> void;

    [[nodiscard]]
    auto unused_size() const noexcept -> std::size_t;

    [[nodiscard]]
    auto used_size() const noexcept -> std::size_t;

    void clear() noexcept;

private:
    [[nodiscard]]
    auto current_chunk_size() const noexcept -> std::size_t;

    static auto expand(allocator & chunk_list, std::size_t size) -> void;

    [[nodiscard]]
    static auto calc_real_chunk_size(std::size_t size) -> std::size_t;
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ZONE_ALLOCATOR
