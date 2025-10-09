#include <iostream>
#include <unistd.h>
#include "NetpbmImageFactory.h"
#include "NetPBM_IO.h"
#include "kernel.h"


int main()
{
    std::vector<std::string> channel_keys{"R", "G", "B"};
//    auto mchi = new MultiChannelImage<3, u8>(1000, 1000, channel_keys);
    auto pgm = NetPBM_IO::readPGMfromFile("../examples/11zon_example_1.pgm");
    auto ppm = NetPBM_IO::readPPMfromFile("../examples/example_0.ppm");
    auto pbm = NetPBM_IO::readPBMfromFile("../examples/example_0.pbm");
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
    k_wrapper->kernel = blur_kernel;

    Kernel::apply(pbm, k_wrapper);
    flag all_zeros = true;
    auto channel = pbm->getChannel("BW");
    auto ch_size = channel->size();
    for (u32 i = 0; i < ch_size; i++) {
        if ((*channel)[i] != 0) all_zeros = false;
    }
    std::cout << std::to_string(all_zeros);
    NetPBM_IO::writePBMtoFile(pbm, "../examples/test3.pbm");


    delete pbm;
    delete pgm;
    delete ppm;
    delete k_wrapper;
}
