#include <iostream>
#include <unistd.h>
#include <NetpbmImageFactory.h>

//TODO: add factory for images
int main()
{
    std::vector<std::string> channel_keys{"R", "G", "B"};
    auto a = new MultiChannelImage<3, u8>(1000, 1000, channel_keys);
    auto b = NetpbmImageFactory::createPPM();
    //TODO: make NetpbmIO use factory
}
