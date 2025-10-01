#include <iostream>
#include <unistd.h>
#include "NetpbmImageFactory.h"
#include "NetPBM_IO.h"
#include "kernel.h"


int main()
{
    std::vector<std::string> channel_keys{"R", "G", "B"};
    auto mchi = new MultiChannelImage<3, u8>(1000, 1000, channel_keys);
    auto pgm = NetpbmImageFactory::createPGM(1000, 1000);
    auto ppm = NetPBM_IO::readPPMfromFile("../examples/example_0.ppm");
    std::vector<std::vector<f32>> blur_kernel = {
            {1.f / 9, 1.f / 9, 1.f / 9},
            {1.f / 9, 1.f / 9, 1.f / 9},
            {1.f / 9, 1.f / 9, 1.f / 9}
    };
    std::vector<std::vector<f32>> sharpen_kernel = {
            {-0.f, -0.25f, -0.f},
            {-0.25f, 2.f, -0.25f},
            {-0.f, -0.25f, 0.f}
    };
    auto k_wrapper = new Kernel::Kernel();
    k_wrapper->height = 3;
    k_wrapper->width = 3;
    k_wrapper->kernel = sharpen_kernel;

    Kernel::apply(ppm, k_wrapper);
    NetPBM_IO::writePPMtoFile(ppm, "../examples/test2.ppm");
}
