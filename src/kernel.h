//
// Created by Besnik Nuro on 17/03/25.
//

#ifndef KERNEL_IMAGE_PROCESSING_KERNEL_H
#define KERNEL_IMAGE_PROCESSING_KERNEL_H

#include <algorithm>

#include "types.h"
#include "MultiChannelImage.h"

namespace Kernel {

    //TODO: implement kernel
    class Kernel {


    };

    //TODO: rewrite
    template<u8 channel_num, typename T>
    static MultiChannelImage<channel_num, T> apply(const MultiChannelImage<channel_num, T> & input,
                        const std::vector<std::vector<float>>& kernel) {
        int k_height = kernel.size();
        int k_width = kernel[0].size();
        int pad_y = k_height / 2;
        int pad_x = k_width / 2;

        MultiChannelImage<channel_num, T> output(input.width, input.height);

        for (int y = 0; y < input.height; ++y) {
            for (int x = 0; x < input.width; ++x) {
                std::array<f32, channel_num> acc = {0};

                for (int ky = 0; ky < k_height; ++ky) {
                    for (int kx = 0; kx < k_width; ++kx) {
                        int ix = x + kx - pad_x;
                        int iy = y + ky - pad_y;

                        if (ix >= 0 && ix < input.width && iy >= 0 && iy < input.height) {
                            auto pixel = input.at(ix, iy);
                            float coeff = kernel[ky][kx];
                            for (int c = 0; c < channel_num; ++c)
                                acc[c] += pixel[c] * coeff;
                        }
                    }
                }

                auto& out = output.at(x, y);
                for (int c = 0; c < channel_num; ++c)
                    out[c] = std::clamp<u8>(acc[c], 0, 255);
            }
        }

        return output;
    }

}


#endif //KERNEL_IMAGE_PROCESSING_KERNEL_H
