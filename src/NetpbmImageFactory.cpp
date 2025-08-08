//
// Created by Besnik Nuro on 08/08/25.
//

#include "NetpbmImageFactory.h"

std::unique_ptr<PPM> NetpbmImageFactory::createPPM() {
    auto rgb_keys = std::vector<std::string>{"R", "G", "B"};
    return std::make_unique<PPM>(0, 0, rgb_keys);
}

