//
// Created by Besnik Nuro on 08/08/25.
//

#include "NetpbmImageFactory.h"

std::unique_ptr<PPM> NetpbmImageFactory::createPPM(u32 width, u32 height, u32 maxVal) {
    auto rgb_keys = std::vector<std::string>{"R", "G", "B"};
    return std::make_unique<PPM>(width, height, rgb_keys);
}

std::unique_ptr<PGM> NetpbmImageFactory::createPGM(u32 width, u32 height, u32 maxVal) {
    auto gray_key = std::vector<std::string>{"Gray"};
    return std::make_unique<PGM>(width, height, gray_key);
}

