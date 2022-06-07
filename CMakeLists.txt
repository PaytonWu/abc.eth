# CMakeList.txt : CMake project for rlp-c, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("rlp-c")

include_directories(.)

# Add source to this project's executable.
add_library(rlp-c "rlp-c.cpp" "rlp/versioning.h" "rlp/v1/object_fwd.h" "rlp/object_fwd_decl.h" "rlp/cpp_version.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET rlp-c PROPERTY CXX_STANDARD 20)
endif()

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")

    # common compile options
    add_compile_options(
        /Zc:__cplusplus       # https://docs.microsoft.com/en-us/cpp/build/reference/zc-cplusplus
        /Zc:externConstexpr   # https://docs.microsoft.com/en-us/cpp/build/reference/zc-externconstexpr
        /Zc:referenceBinding  # https://docs.microsoft.com/en-us/cpp/build/reference/zc-referencebinding-enforce-reference-binding-rules
        /Zc:inline            # https://docs.microsoft.com/en-us/cpp/build/reference/zc-inline-remove-unreferenced-comdat
        /Zc:rvalueCast        # https://docs.microsoft.com/en-us/cpp/build/reference/zc-rvaluecast-enforce-type-conversion-rules
        /Zc:strictStrings     # https://docs.microsoft.com/en-us/cpp/build/reference/zc-strictstrings-disable-string-literal-type-conversion
        /Zc:ternary           # https://docs.microsoft.com/en-us/cpp/build/reference/zc-ternary
        /Zc:throwingNew       # https://docs.microsoft.com/en-us/cpp/build/reference/zc-throwingnew-assume-operator-new-throws
        /Zc:char8_t
        /Zc:hiddenFriend
        /Zc:externC
        /Zc:lambda
        /permissive-          # https://blogs.msdn.microsoft.com/vcblog/2016/11/16/permissive-switch/
                              # https://blogs.msdn.microsoft.com/vcblog/2017/09/11/two-phase-name-lookup-support-comes-to-msvc/
                              # https://docs.microsoft.com/en-us/cpp/build/reference/permissive-standards-conformance
        /volatile:iso         # https://docs.microsoft.com/en-us/cpp/build/reference/volatile-volatile-keyword-interpretation
        /GS
        /Zi
        /EHsc
        /fp:precise
        /errorReport:prompt
        /diagnostics:caret    # https://docs.microsoft.com/en-us/cpp/build/reference/diagnostics-compiler-diagnostic-options
        /utf-8                # https://docs.microsoft.com/en-us/cpp/build/reference/utf-8-set-source-and-executable-character-sets-to-utf-8
        /WL                   # https://docs.microsoft.com/en-us/cpp/build/reference/wl-enable-one-line-diagnostics
    )

    if (CMAKE_CXX_FLAGS MATCHES "/W[0-3]")
        string(REGEX REPLACE "/W[0-3]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        add_compile_options(/W4)
    endif()

    add_definitions(
        -D_SCL_SECURE_NO_WARNINGS
        -D_CRT_SECURE_NO_WARNINGS
        -DNOMINMAX
        -D_WIN32_WINNT=0x0600   # Vista and above
        -D_WINDOWS
        -D_UNICODE
        -DUNICODE
        -DWIN32_LEAN_AND_MEAN)
endif()

# TODO: Add tests and install targets if needed.
