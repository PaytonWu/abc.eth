# CMakeList.txt : CMake project for rlp-c, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("rlp-c")

include_directories(.)

# Add source to this project's executable.
add_library(rlp-c "rlp-c.cpp" "rlp/versioning.h" "rlp/v1/object_fwd.h" "rlp/object_fwd_decl.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET rlp-c PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
