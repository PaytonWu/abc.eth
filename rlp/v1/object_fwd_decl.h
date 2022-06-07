// Copyright(c) 2022 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(RLP_V1_OBJECT_FWD_DECL_H)
#define RLP_V1_OBJECT_FWD_DECL_H

#pragma once

#include "rlp/versioning.h"

#include <typeinfo>

namespace rlp {

RLP_API_VERSION_NAMESPACE(v1) {

    namespace type {

    enum class object_type : uint8_t {
        NIL = 0x00,
        BOOLEAN = 0x01,
        POSITIVE_INTEGER = 0x02,
        NEGATIVE_INTEGER = 0x03,
        STR = 0x04,
        BIN = 0x05,
        ARRAY = 0x05,
        MAP = 0x06,
        EXT = 0x07
    };

    }

    struct object;
    struct object_kv;

    struct object_array;
    struct object_map;
    struct object_str;
    struct object_bin;
    struct object_ext;

    namespace adaptor {
    template <typename T, typename Enabler = void>
    struct as;
    } // namespace adaptor

    template <typename T>
    struct has_as;

    class type_error;

} // RLP_API_VERSION_NAMESPACE(v1)

} // namespace rlp

#endif
