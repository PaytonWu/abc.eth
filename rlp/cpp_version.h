// Copyright(c) 2022 - present, Payton Wu (payton.wu@outlook.com) & contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#if !defined(RLP_CPP_VERSION_H)
#define RLP_CPP_VERSION_H

#pragma once

#if defined(_MSC_VER)
#  if _MSC_VER < 1930   // RLP-C is implemented & tested on VS2022
#    error "RLP-C is implemented using VS2022. Thus required _MSC_VER >= 1930. You can change the above requirement as needed"
#  endif
#elif (__cplusplus < 202002L)
#  error "RLP-C is implemented using C++20. You can change the above requirement as needed.
#endif

#if defined(_MSVC_LANG)
#  define RLP_CPP_VERSION _MSVC_LANG
#else
#  define RLP_CPP_VERSION __cplusplus
#endif


#endif
