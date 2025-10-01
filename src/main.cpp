#include <iostream>
#include <unistd.h>
#include "NetpbmImageFactory.h"
#include "NetPBM_IO.h"
#include "kernel.h"

//TODO: add factory for images
int main()
{
    std::vector<std::string> channel_keys{"R", "G", "B"};
    auto mchi = new MultiChannelImage<3, u8>(1000, 1000, channel_keys);
    auto pgm = NetpbmImageFactory::createPGM(1000, 1000);
    auto ppm = NetPBM_IO::readPPMfromFile("../examples/example_2.ppm");
    std::vector<std::vector<f32>> kernel = {
            {1.f / 9, 1.f / 9, 1.f / 9},
            {1.f / 9, 1.f / 9, 1.f / 9},
            {1.f / 9, 1.f / 9, 1.f / 9}
    };
    auto k_wrapper = new Kernel::Kernel();
    k_wrapper->height = 3;
    k_wrapper->width = 3;
    k_wrapper->kernel = kernel;

    auto r = ppm->getChannel("R");
    auto g = ppm->getChannel("G");
    auto b = ppm->getChannel("B");
    std::cout << "R channel size: " << r->size() << "\n";
    auto new_r = Kernel::apply(r, ppm->getWidth(), ppm->getHeight(), k_wrapper);
    auto new_g = Kernel::apply(g, ppm->getWidth(), ppm->getHeight(), k_wrapper);
    auto new_b = Kernel::apply(b, ppm->getWidth(), ppm->getHeight(), k_wrapper);
    ppm->setChannel("R", new_r);
    ppm->setChannel("G", new_g);
    ppm->setChannel("B", new_b);
    NetPBM_IO::writePPMtoFile(ppm, "../examples/test2.ppm");
    //TODO: make NetpbmIO use factory
}
