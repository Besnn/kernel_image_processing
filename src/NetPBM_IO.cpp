//
// Created by Besnik Nuro on 09/08/25.
//
#include <fstream>
#include <iostream>
#include "NetPBM_IO.h"

void NetPBM_IO::skipComments(std::istream &is) {
    while (true) {
        // Skip whitespace
        while (std::isspace(is.peek())) {
            is.get();
        }
        // Skip comments
        if (is.peek() == '#') {
            std::string dummy;
            std::getline(is, dummy);
        } else {
            break;
        }
    }
}

std::unique_ptr<PPM> NetPBM_IO::readPPMfromFile(const std::string &path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file: " + path);
    }
    //FIXME: make it only for PPM files
    std::string magic;
    file >> magic;
    if (magic.size() != 2 || magic[0] != 'P') {
        throw std::runtime_error("Invalid Netpbm magic number");
    }
    int format = magic[1] - '0';
    if (format < 1 || format > 6) {
        throw std::runtime_error("Unsupported Netpbm format: " + magic);
    }
    //FIXME: make this function a wrapper that calls a specialized function (u8 or u16)
    skipComments(file);

    u32 width = 0;
    u32 height = 0;
    u32 maxVal = 0;

    file >> width;
    skipComments(file);
    file >> height;

    if (format != 1 && format != 4) { // Not PBM
        skipComments(file);
        file >> maxVal;
    }

    if (maxVal != 255) throw std::runtime_error("Color depth not supported; maxVal=" + std::to_string(maxVal));

    file.get(); // Eat one whitespace/newline after header

    auto ppm = NetpbmImageFactory::createPPM(width, height, maxVal);

//    ppm->setWidth(width);
//    ppm->setHeight(height);

    std::string file_signature =
            magic +
            "\n" +
            std::to_string(width) +
            " " +
            std::to_string(height) +
            "\n" +
            std::to_string(maxVal) +
            "\n";

    ppm->setFileSignature(file_signature);

    const u8 channel_count = 3;

    std::vector<u8> pixel_buffer(channel_count * width * height);

    if (format == 1 || format == 2 || format == 3) {
        // ASCII formats
//        for (u32 i = 0; i < width * height; ++i) {
//            u16 val;
//            file >> val;
//            img.pixels[i] = static_cast<unsigned char>(val);
//        }
    } else {
        // Binary formats
//        std::vector<u8> * pixel_buffer = new std::vector<u8>(width * height);
        file.read(reinterpret_cast<char *>(pixel_buffer.data()), channel_count * width * height * sizeof(u8));

        if (!file) {
            throw std::runtime_error("File ended before expected pixel data");
        }
        auto r_channel = std::make_unique<Channel<u8>>(width * height);
        auto g_channel = std::make_unique<Channel<u8>>(width * height);
        auto b_channel = std::make_unique<Channel<u8>>(width * height);

        u32 N = pixel_buffer.size() / 3;
        const u8 * p = pixel_buffer.data();
        for (u32 i = 0; i < N; ++i) {
            r_channel->at(i) = static_cast<u8>(pixel_buffer[i * 3 + 0]);
            g_channel->at(i) = static_cast<u8>(pixel_buffer[i * 3 + 1]);
            b_channel->at(i) = static_cast<u8>(pixel_buffer[i * 3 + 2]);
        }
//        TODO: delete this
        for (u32 i = 0; i < N; i++) {
            if (r_channel->at(i) != 0)
                std::cout << std::to_string(i) << ": " << r_channel->at(i) << "\n";
        }
    }

    return ppm;
}



