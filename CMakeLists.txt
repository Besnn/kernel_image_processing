cmake_minimum_required(VERSION 3.25)
project(Kernel_Image_Processing)

set(CMAKE_CXX_STANDARD 17)

add_executable(Kernel_Image_Processing
        main.cpp
        image_formats/PNM.h image_formats/PNM.cpp
        image_formats/PBM.h image_formats/PBM.cpp
        image_formats/PPM.h image_formats/PPM.cpp
        core/ImageContainer.h core/ImageContainer.cpp
        core/kernel.h core/types.h
        codecs/PBMCodec.h codecs/PBMCodec.cpp)
