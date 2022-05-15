cmake_minimum_required(VERSION 3.4.1)

set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 11)
add_definitions(-DBLS_ETH -DMCL_USE_VINT -DMCL_VINT_FIXED_BUFFER -DMCL_DONT_USE_OPENSSL -DMCL_DONT_USE_XBYAK -DMCL_SIZEOF_UNIT=4 -DMCL_MAX_BIT_SIZE=384 -DCYBOZU_MINIMUM_EXCEPTION)

add_library(cpp
            SHARED
            ../cpp/mcl/src/fp.cpp
            ../cpp/bls/src/bls_c384_256.cpp
            cpp_adapter.cpp
            hashes.h
)

# Specifies a path to native header files.
include_directories(
            ../cpp/mcl/src
            ../cpp/mcl/include
            ../cpp/bls/include
            ../cpp/bls/src
)

target_link_libraries(cpp
log
android)
