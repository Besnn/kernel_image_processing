#include <iostream>

#include "src/codecs/PBMCodec.h"

int main() {
    auto pixelmap = std::vector<bool>({false});
    ChannelContainer channels;    channels.emplace_back(pixelmap);
    auto pbm = new PNM(1, 1, P4, channels);

    return 0;
}
