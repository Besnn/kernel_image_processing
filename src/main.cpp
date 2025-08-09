#include <iostream>
#include <unistd.h>
#include <NetpbmImageFactory.h>

//TODO: add factory for images
int main()
{
    std::vector<std::string> channel_keys{"R", "G", "B"};
    auto mchi = new MultiChannelImage<3, u8>(1000, 1000, channel_keys);
    auto ppm = NetpbmImageFactory::createPPM(1000, 1000);
    auto pgm = NetpbmImageFactory::createPGM(1000, 1000);
    //TODO: make NetpbmIO use factory
}
