cmake_minimum_required(VERSION 3.25)
project(Kernel_Image_Processing)

set(CMAKE_CXX_STANDARD 17)
include_directories(${CMAKE_SOURCE_DIR})
include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(kernel STATIC
        src/image_formats/PNM.h src/image_formats/PNM.cpp
        src/image_formats/PBM.h src/image_formats/PBM.cpp
        src/image_formats/PPM.h src/image_formats/PPM.cpp
        src/core/ImageContainer.h src/core/ImageContainer.cpp
        src/core/kernel.h src/core/types.h
        src/codecs/PBMCodec.h src/codecs/PBMCodec.cpp)

target_include_directories(kernel PUBLIC ${CMAKE_SOURCE_DIR}/src)

# Main
add_executable(Kernel_Image_Processing src/main.cpp)
target_link_libraries(Kernel_Image_Processing PRIVATE kernel)

# Test
add_executable(Test tests/test_example.cpp)
target_link_libraries(Test PRIVATE gtest gtest_main kernel)
#target_include_directories(
#        Kernel_Image_Processing
#        PRIVATE
#        ${CMAKE_SOURCE_DIR}
#)
include(GoogleTest)
gtest_discover_tests(Test)