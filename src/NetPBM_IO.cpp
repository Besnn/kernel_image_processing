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
    if (!file)
        throw std::runtime_error("Cannot access file: " + path);

    std::string magic;
    file >> magic;
    if (magic.size() != 2 || magic[0] != 'P')
        throw std::runtime_error("Invalid Netpbm magic number");

    int format = magic[1] - '0';
    if (format != 3 && format != 6)
        throw std::runtime_error("Unsupported PPM format: " + magic);

    skipComments(file);

    u32 width = 0;
    u32 height = 0;
    u32 maxVal = 0;

    file >> width;
    skipComments(file);
    file >> height;
    skipComments(file);
    file >> maxVal;

    if (maxVal != 255)
        throw std::runtime_error("Only 8-bit PPM (maxVal=255) supported");

    file.get(); // consume trailing newline/space after header

    auto ppm = NetpbmImageFactory::createPPM(width, height, maxVal);

    std::string file_signature =
      magic + "\n" +
      std::to_string(width) + " " + std::to_string(height) + "\n" +
      std::to_string(maxVal) + "\n";

    ppm->setFileSignature(file_signature);

    const u8 channel_count = 3;
    const u32 N = width * height;

    auto r_channel = new Channel<u8>(N);
    auto g_channel = new Channel<u8>(N);
    auto b_channel = new Channel<u8>(N);

    if (format == 3) {
        // -------- ASCII PPM (P3) --------
        for (u32 i = 0; i < N; ++i) {
            int r, g, b;
            file >> r >> g >> b;
            if (file.fail())
                throw std::runtime_error("Unexpected end of ASCII PPM data");

            (*r_channel)[i] = static_cast<u8>(r);
            (*g_channel)[i] = static_cast<u8>(g);
            (*b_channel)[i] = static_cast<u8>(b);
        }
    } else {
        // -------- Binary PPM (P6) --------
        std::vector<u8> pixel_buffer(channel_count * N);
        file.read(reinterpret_cast<char*>(pixel_buffer.data()), channel_count * N);

        if (!file)
            throw std::runtime_error("File ended before expected pixel data");

        for (u32 i = 0; i < N; ++i) {
            (*r_channel)[i] = pixel_buffer[i * 3 + 0];
            (*g_channel)[i] = pixel_buffer[i * 3 + 1];
            (*b_channel)[i] = pixel_buffer[i * 3 + 2];
        }
    }

    ppm->setChannel("R", r_channel);
    ppm->setChannel("G", g_channel);
    ppm->setChannel("B", b_channel);

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

PBM *NetPBM_IO::readPBMfromFile(const std::string &path)
{
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
    if (format != 1 && format != 4) {
        throw std::runtime_error("Unsupported PBM format: " + magic);
    }

    skipComments(file);

    u32 width = 0;
    u32 height = 0;

    file >> width;
    skipComments(file);
    file >> height;

    file.get(); // consume trailing whitespace/newline

    auto pbm = NetpbmImageFactory::createPBM(width, height);

    std::string file_signature =
      magic + "\n" +
      std::to_string(width) + " " + std::to_string(height) + "\n";
    pbm->setFileSignature(file_signature);

    auto mono_channel = new Channel<bool>(width * height);

    if (format == 1) {
        // ASCII PBM
        for (u32 i = 0; i < width * height; ++i) {
            int bit;
            file >> bit;
            if (file.fail())
                throw std::runtime_error("Unexpected end of ASCII PBM data");

            (*mono_channel)[i] = static_cast<bool>(bit);
        }
    } else {
        // Binary PBM (P4)
        size_t row_bytes = (width + 7) / 8;
        std::vector<u8> row_buffer(row_bytes);

        for (u32 y = 0; y < height; ++y) {
            file.read(reinterpret_cast<char*>(row_buffer.data()), row_bytes);
            if (!file)
                throw std::runtime_error("Unexpected end of binary PBM data");

            for (u32 x = 0; x < width; ++x) {
                u8 byte = row_buffer[x / 8];
                bool bit = (byte & (0x80 >> (x % 8))) != 0;
                (*mono_channel)[y * width + x] = bit;
            }
        }
    }

    pbm->setChannel("BW", mono_channel);
    return pbm;
}

void NetPBM_IO::writePBMtoFile(PBM *pbm, const std::string &path)
{
    std::ofstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot access file: " + path);
    }

    const std::string file_signature = pbm->getFileSignature();
    const u32 width = pbm->getWidth();
    const u32 height = pbm->getHeight();

    // Validate magic number
    if (file_signature.size() < 2 || file_signature[0] != 'P' ||
        (file_signature[1] != '1' && file_signature[1] != '4')) {
        throw std::runtime_error("Invalid or missing PBM file signature");
    }

    file << file_signature; // already includes \n after header typically

    // Retrieve channel
    auto mono_channel = pbm->getChannel("BW");
    if (!mono_channel) {
        throw std::runtime_error("PBM missing Mono channel");
    }

//    const u32 N = mono_channel->size();
//    if (N != width * height) {
//        throw std::runtime_error("PBM channel size mismatch");
//    }

    bool binary = (file_signature[1] == '4');

    if (binary) {
        // ---- Binary PBM (P4) ----
        const size_t row_bytes = (width + 7) / 8;
        std::vector<u8> row_buffer(row_bytes);

        for (u32 y = 0; y < height; ++y) {
            std::fill(row_buffer.begin(), row_buffer.end(), 0);

            for (u32 x = 0; x < width; ++x) {
                bool bit;
                if constexpr (std::is_same_v<typename Channel<bool>::value_type, bool>)
                    bit = (*mono_channel)[y * width + x];
                else
                    bit = ((*mono_channel)[y * width + x] > 127);

                if (bit)
                    row_buffer[x / 8] |= (0x80 >> (x % 8));
            }

            file.write(reinterpret_cast<char*>(row_buffer.data()), row_bytes);
        }
    } else {
        // ---- ASCII PBM (P1) ----
        for (u32 y = 0; y < height; ++y) {
            for (u32 x = 0; x < width; ++x) {
                bool bit;
                if constexpr (std::is_same_v<typename Channel<bool>::value_type, bool>)
                    bit = (*mono_channel)[y * width + x];
                else
                    bit = ((*mono_channel)[y * width + x] > 127);

                file << (bit ? '1' : '0');
                if (x < width - 1)
                    file << ' ';
            }
            file << '\n';
        }
    }

    if (!file) {
        throw std::runtime_error("Failed writing PBM to file: " + path);
    }
}


