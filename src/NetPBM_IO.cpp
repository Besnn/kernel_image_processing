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

PPM * NetPBM_IO::readPPMfromFile(const std::string &path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot access file: " + path);
    }

    std::string magic;
    file >> magic;
    if (magic.size() != 2 || magic[0] != 'P') {
        throw std::runtime_error("Invalid Netpbm magic number");
    }
    int format = magic[1] - '0';
    if (format < 1 || format > 6) {
        throw std::runtime_error("Unsupported Netpbm format: " + magic);
    }

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

    std::vector<u8> pixel_buffer;
    pixel_buffer.resize(channel_count * width * height);

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
        auto r_channel = new Channel<u8>(width * height);
        auto g_channel = new Channel<u8>(width * height);
        auto b_channel = new Channel<u8>(width * height);

        u32 N = r_channel->size();
        for (u32 i = 0; i < N; ++i) {
            (*r_channel)[i] = pixel_buffer[i * 3 + 0];
            (*g_channel)[i] = pixel_buffer[i * 3 + 1];
            (*b_channel)[i] = pixel_buffer[i * 3 + 2];
        }


        ppm->setChannel("R", r_channel);
        ppm->setChannel("G", g_channel);
        ppm->setChannel("B", b_channel);
    }

    return ppm;
}

void NetPBM_IO::writePPMtoFile(PPM * ppm, const std::string &path) {
    std::ofstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot access file: " + path);
    }
    std::string file_signature = ppm->getFileSignature();
    u32 width = ppm->getWidth();
    u32 height = ppm->getHeight();
    u8 channel_count = ppm->getChannels().size();

    file << file_signature;
    std::vector<u8> pixel_buffer;
    pixel_buffer.resize(channel_count * height * width);

    auto r_channel = ppm->getChannel("R");
    auto g_channel = ppm->getChannel("G");
    auto b_channel = ppm->getChannel("B");

    u32 N = r_channel->size();
    u32 i = 0;
    for (; i < N; i++) {
        pixel_buffer[i * 3 + 0] = (*r_channel)[i];
        pixel_buffer[i * 3 + 1] = (*g_channel)[i];
        pixel_buffer[i * 3 + 2] = (*b_channel)[i];
    }


    file.write(reinterpret_cast<char *>(pixel_buffer.data()), pixel_buffer.size());

    return;
}

PGM *NetPBM_IO::readPGMfromFile(const std::string &path)
{
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot access file: " + path);
    }
    //TODO: refactor logic

    std::string magic;
    file >> magic;
    if (magic.size() != 2 || magic[0] != 'P') {
        throw std::runtime_error("Invalid Netpbm magic number");
    }
    int format = magic[1] - '0';
    if (format < 1 || format > 6) {
        throw std::runtime_error("Unsupported Netpbm format: " + magic);
    }

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

    auto pgm = NetpbmImageFactory::createPGM(width, height, maxVal);

    std::string file_signature =
      magic +
      "\n" +
      std::to_string(width) +
      " " +
      std::to_string(height) +
      "\n" +
      std::to_string(maxVal) +
      "\n";

    pgm->setFileSignature(file_signature);

    std::vector<u8> pixel_buffer;
    pixel_buffer.resize(width * height);

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
        file.read(reinterpret_cast<char *>(pixel_buffer.data()), width * height * sizeof(u8));

        if (!file) {
            throw std::runtime_error("File ended before expected pixel data");
        }
        auto gray_channel = new Channel<u8>(width * height);

        u32 N = gray_channel->size();
        for (u32 i = 0; i < N; ++i) {
            (*gray_channel)[i] = pixel_buffer[i];
        }


        pgm->setChannel("Gray", gray_channel);
    }

    return pgm;
}

void NetPBM_IO::writePGMtoFile(PGM * pgm, const std::string &path)
{
    std::ofstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot access file: " + path);
    }
    std::string file_signature = pgm->getFileSignature();
    u32 width = pgm->getWidth();
    u32 height = pgm->getHeight();
    u8 channel_count = pgm->getChannels().size();

    file << file_signature;
    std::vector<u8> pixel_buffer;
    pixel_buffer.resize(channel_count * height * width);

    auto gray_channel = pgm->getChannel("Gray");

    u32 N = gray_channel->size();
    u32 i = 0;
    for (; i < N; i++) {
        pixel_buffer[i] = (*gray_channel)[i];
    }


    file.write(reinterpret_cast<char *>(pixel_buffer.data()), pixel_buffer.size());

    return;
}

