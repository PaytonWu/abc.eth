// Copyright(c) 2023 - present, Payton Wu (payton.wu@outlook.com) & the contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#ifndef ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ZONE_CONSTRUCTOR
#define ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ZONE_CONSTRUCTOR

#pragma once

#include <utility>

namespace abc::ethereum::rlp::zone {

struct finalizer {
    auto (*finalize)(void *) -> void;
    void * ptr;

    auto operator()() -> void {
        finalize(ptr);
    }
};

template <typename T>
class constructor {
public:
    template <typename ... ArgsT>
    [[nodiscard]]
    static auto construct(void * ptr, ArgsT &&... args) -> T * {
        return new (ptr) T{ std::forward<ArgsT>(args)... };
    }

    static auto default_destructor(void * ptr) -> void {
        static_cast<T *>(ptr)->~T();
    }

    static auto default_deleter(void * ptr) -> void {
        delete static_cast<T *>(ptr);
    }
};

}

#endif //ABC_ETH_INCLUDE_ABC_ETHEREUM_RLP_ZONE_CONSTRUCTOR
