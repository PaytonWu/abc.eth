// Copyright(c) 2022 - present, Payton Wu (payton.wu@outlook.com) & abc contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(RLP_VERSION_H)
#define RLP_VERSION_H

#pragma once

#if !defined(RLP_DEFAULT_API_VERSION)
#define RLP_DEFAULT_API_VERSION 1
#endif

#define RLP_DEFAULT_API_NS RLP_DETAIL_PP_CAT(v, RLP_DEFAULT_API_VERSION)

#if RLP_DEFAULT_API_VERSION == 1
#define RLP_DETAIL_PP_ENABLE_NS_v1()
#else
#error
#endif

#define RLP_DETAIL_PP_CAT(a, ...) RLP_DETAIL_PP_PRIMITIVE_CAT(a, __VA_ARGS__)
#define RLP_DETAIL_PP_PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define RLP_DETAIL_PP_IIF(c) RLP_DETAIL_PP_PRIMITIVE_CAT(RLP_DETAIL_PP_IIF_, c)
#define RLP_DETAIL_PP_IIF_0(t, ...) __VA_ARGS__
#define RLP_DETAIL_PP_IIF_1(t, ...) t

#define RLP_DETAIL_PP_PROBE(x) x, 1

#if defined(_MSC_VER)

#define RLP_DETAIL_PP_MSVC_VA_ARGS_WORKAROUND(define, args) define args
#define RLP_DETAIL_PP_CHECK(...) RLP_DETAIL_PP_MSVC_VA_ARGS_WORKAROUND(RLP_DETAIL_PP_CHECK_N, (__VA_ARGS__, 0, 0))
#define RLP_DETAIL_PP_CHECK_N(x, n, ...) n

#else  // defined(__MSC_VER)

#define RLP_DETAIL_PP_CHECK(...) RLP_DETAIL_PP_CHECK_N(__VA_ARGS__, 0, 0)
#define RLP_DETAIL_PP_CHECK_N(x, n, ...) n

#endif // defined(__MSC_VER)


#define RLP_DETAIL_PP_NS_ENABLED_PROBE(ns)            RLP_DETAIL_PP_NS_ENABLED_PROBE_PROXY( RLP_DETAIL_PP_ENABLE_NS_##ns )
#define RLP_DETAIL_PP_NS_ENABLED_PROBE_PROXY(...)     RLP_DETAIL_PP_NS_ENABLED_PROBE_PRIMIVIE(__VA_ARGS__)
#define RLP_DETAIL_PP_NS_ENABLED_PROBE_PRIMIVIE(x)    RLP_DETAIL_PP_NS_ENABLED_PROBE_COMBINE_ x
#define RLP_DETAIL_PP_NS_ENABLED_PROBE_COMBINE_(...)  RLP_DETAIL_PP_PROBE(~)

#define RLP_DETAIL_PP_IS_NS_ENABLED(ns) RLP_DETAIL_PP_CHECK(RLP_DETAIL_PP_NS_ENABLED_PROBE(ns))

#if __cplusplus < 201103L
#define RLP_API_VERSION_NAMESPACE(ns) RLP_DETAIL_PP_IIF(RLP_DETAIL_PP_IS_NS_ENABLED(ns)) \
    (namespace ns{}; using namespace ns; namespace ns, \
     namespace ns)

#else  // __cplusplus < 201103L

#define RLP_API_VERSION_NAMESPACE(ns) RLP_DETAIL_PP_IIF(RLP_DETAIL_PP_IS_NS_ENABLED(ns)) \
    (inline namespace ns, namespace ns)

#endif // __cplusplus < 201103L

#endif // RLP_VERSIONING_HPP
