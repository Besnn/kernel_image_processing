//
// Created by Besnik Nuro on 08/08/25.
//

#include "NetpbmImageFactory.h"

PPM * NetpbmImageFactory::createPPM(u32 width, u32 height, u32 maxVal) {
    auto rgb_keys = std::vector<std::string>{"R", "G", "B"};
    return new PPM (width, height, rgb_keys);
}

PGM * NetpbmImageFactory::createPGM(u32 width, u32 height, u32 maxVal) {
    auto gray_key = std::vector<std::string>{"Gray"};
    return new PGM(width, height, gray_key);
}

//NOTE:
// C++ te kam dhjere,
// s'te kuptova asnjehere
