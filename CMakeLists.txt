cmake_minimum_required(VERSION 3.25)
project(Kernel_Image_Processing)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -stdlib=libc++")


include_directories(${CMAKE_SOURCE_DIR})
include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(kernel INTERFACE)

target_include_directories(kernel INTERFACE ${CMAKE_SOURCE_DIR}/src)

# Main
add_executable(Kernel_Image_Processing src/main.cpp
        src/NetpbmImageFactory.cpp
        src/NetpbmImageFactory.h
        src/NetPBM_IO.cpp
        src/test_utilities.hpp
)
target_link_libraries(Kernel_Image_Processing PRIVATE kernel)

# Test
add_executable(Test
        src/NetPBM_IO.h
        src/NetPBM_IO.cpp
        src/MultiChannelImage.h
        tests/ppm_factory_test.cpp
        src/NetpbmImageFactory.cpp
        tests/pgm_factory_test.cpp
        src/test_utilities.hpp
        tests/netpbm_io_tests.cpp
)
target_link_libraries(Test PRIVATE gtest gtest_main kernel)
#target_include_directories(
#        Kernel_Image_Processing
#        PRIVATE
#        ${CMAKE_SOURCE_DIR}
#)
include(GoogleTest)
gtest_discover_tests(Test)