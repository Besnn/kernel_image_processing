#include <iostream>
#include <unistd.h>
#include "NetpbmImageFactory.h"
#include "NetPBM_IO.h"
#include "kernel.h"


int main()
{
    auto pbm_p1 = NetPBM_IO::readPBMfromFile("../examples/p1_example_a.pbm");
    auto pgm_p2 = NetPBM_IO::readPGMfromFile("../examples/p2_example_3.pgm");
    auto ppm_p3 = NetPBM_IO::readPPMfromFile("../examples/p3_example_sprite.ppm");
    auto pbm_p4 = NetPBM_IO::readPBMfromFile("../examples/p4_example_1.pbm");
    auto pgm_p5 = NetPBM_IO::readPGMfromFile("../examples/p5_example_1.pgm");
    auto ppm_p6 = NetPBM_IO::readPPMfromFile("../examples/p6_example_0.ppm");

    // EXAMPLE KERNELS
    std::vector<std::vector<f32>> box_blur_3x3 = {
            {1.f / 9, 1.f / 9, 1.f / 9},
            {1.f / 9, 1.f / 9, 1.f / 9},
            {1.f / 9, 1.f / 9, 1.f / 9}
    };

    std::vector<std::vector<f32>> box_blur_5x5 = {
            {1.f / 25, 1.f / 25, 1.f / 25, 1.f / 25, 1.f / 25},
            {1.f / 25, 1.f / 25, 1.f / 25, 1.f / 25, 1.f / 25},
            {1.f / 25, 1.f / 25, 1.f / 25, 1.f / 25, 1.f / 25},
            {1.f / 25, 1.f / 25, 1.f / 25, 1.f / 25, 1.f / 25},
            {1.f / 25, 1.f / 25, 1.f / 25, 1.f / 25, 1.f / 25}
    };

    std::vector<std::vector<f32>> gaussian_blur_3x3 = {
            {1.f / 16, 1.f / 8, 1.f / 16},
            {1.f / 8, 1.f / 4, 1.f / 8},
            {1.f / 16, 1.f / 8, 1.f / 16}
    };

    std::vector<std::vector<f32>> gaussian_blur_5x5 = {
            {1.f / 256, 1.f / 64, 6.f / 256, 1.f / 64, 1.f / 256},
            {1.f / 64, 1.f / 16, 24.f / 256, 1.f / 16, 1.f / 64},
            {6.f / 256, 24.f / 256, 36.f / 256, 24.f / 256, 6.f / 256},
            {1.f / 64, 1.f / 16, 24.f / 256, 1.f / 16, 1.f / 64},
            {1.f / 256, 1.f / 64, 6.f / 256, 1.f / 64, 1.f / 256}
    };

    std::vector<std::vector<f32>> unsharp_masking_5x5 = {
            {-1.f / 256, -1.f / 64, -6.f / 256, -1.f / 64, -1.f / 256},
            {-1.f / 64, -1.f / 16, -24.f / 256, -1.f / 16, -1.f / 64},
            {-6.f / 256, -24.f / 256, 476.f / 256, -24.f / 256, -6.f / 256},
            {-1.f / 64, -1.f / 16, -24.f / 256, -1.f / 16, -1.f / 64},
            {-1.f / 256, -1.f / 64, -6.f / 256, -1.f / 64, -1.f / 256},
    };

    std::vector<std::vector<f32>> sharpen_3x3 = {
            {-0.f, -1.f, -0.f},
            {-1.f, 5.f, -1.f},
            {-0.f, -1.f, -0.f}
    };

    std::vector<std::vector<f32>> emboss_3x3 = {
            {-2.f, -1.f, 0.f},
            {-1.f, 1.f, 1.f},
            {0.f, 1.f, 2.f}
    };

    std::vector<std::vector<f32>> ridge_detection_3x3 = {
            {0.f, -1.f, 0.f},
            {-1.f, 4.f, -1.f},
            {0.f, -1.f, 0.f}
    };

    std::vector<std::vector<f32>> edge_detection_3x3 = {
            {-1.f, -1.f, -1.f},
            {-1.f, 8.f, -1.f},
            {-1.f, -1.f, -1.f}
    };

    std::vector<std::vector<f32>> horizontal_edge_detection_3x3 = {
            {-1.f, -1.f, -1.f},
            {0.f, 0.f, 0.f},
            {1.f, 1.f, 1.f}
    };

    std::vector<std::vector<f32>> vertical_edge_detection_3x3 = {
            {-1.f, 0.f, 1.f},
            {-1.f, 0.f, 1.f},
            {-1.f, 0.f, 1.f}
    };

    std::vector<std::vector<f32>> horizontal_sobel_3x3 = {
            {-1.f, 0.f, 1.f},
            {-2.f, 0.f, 2.f},
            {-1.f, 0.f, 1.f}
    };

    std::vector<std::vector<f32>> vertical_sobel_3x3 = {
            {-1.f, -2.f, -1.f},
            {0.f, 0.f, 0.f},
            {1.f, 2.f, 1.f}
    };

    std::vector<std::vector<f32>> laplacian_3x3 = {
            {0.f, -1.f, 0.f},
            {-1.f, 4.f, -1.f},
            {0.f, -1.f, 0.f}
    };

    std::vector<std::vector<f32>> low_pass_3x3 = {
            {1.f, 1.f, 1.f},
            {1.f, 2.f, 1.f},
            {1.f, 1.f, 1.f}
    };

    std::vector<std::vector<f32>> high_pass_3x3 = {
            {0.f, -1.f, 0.f},
            {-1.f, 4.f, -1.f},
            {0.f, -1.f, 0.f}
    }; // ridge_detection


    auto kernel_wrapper = new Kernel::Kernel(low_pass_3x3);
    Kernel::apply(ppm_p3, kernel_wrapper);

    NetPBM_IO::writePPMtoFile(ppm_p3, "../examples/test_p3_low_pass.ppm");

    delete pbm_p1, pbm_p4;
    delete pgm_p2, pgm_p5;
    delete ppm_p3, ppm_p6;
    delete kernel_wrapper;
}
