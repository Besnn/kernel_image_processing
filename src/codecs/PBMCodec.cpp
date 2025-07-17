//
// Created by Besnik Nuro on 17/03/25.
//

#include "PBMCodec.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

#include "../core/ImageContainer.h"
#include "../image_formats/PBM.h"



ImageContainer PBMCodec::loadFromFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Error: Cannot open PBM file.");
    }

    std::string magicNumber;
    file >> magicNumber;

    bool isBinary = (magicNumber == "P4");
    if (magicNumber != "P1" && magicNumber != "P4") {
        throw std::runtime_error("Error: Unsupported PBM format.");
    }

    int width, height;
    file >> width >> height;

    std::vector<u8> pixelData(width * height, 0);

    if (isBinary) {
        file.ignore(); // Skip single whitespace after header
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width / 8 + (width % 8 ? 1 : 0); j++) {
                unsigned char byte;
                file.read(reinterpret_cast<char*>(&byte), 1);
                for (int bit = 0; bit < 8; bit++) {
                    if (j * 8 + bit < width) {
                        pixelData[i * width + j * 8 + bit] = (byte & (1 << (7 - bit))) ? 255 : 0;
                    }
                }
            }
        }
    } else {
        for (int i = 0; i < width * height; i++) {
            int pixel;
            file >> pixel;
            pixelData[i] = (pixel == 1) ? 255 : 0; // Convert to white (255) or black (0)
        }
    }

    return ImageContainer(width, height, pixelData);
}
