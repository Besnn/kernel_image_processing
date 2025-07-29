//
// Created by Besnik Nuro on 17/03/25.
//

#ifndef KERNEL_IMAGE_PROCESSING_KERNEL_H
#define KERNEL_IMAGE_PROCESSING_KERNEL_H

#include "types.h"

namespace Kernel {

    //TODO: implement kernel
    class kernel {

        //NOTE: asdasd
        //FIXME: asdasdas
    };


    template<int ChannelsNo>
    Image<ChannelsNo> apply(const Image<ChannelsNo>& input,
                        const std::vector<std::vector<float>>& kernel) {
        int kHeight = kernel.size();
        int kWidth = kernel[0].size();
        int padY = kHeight / 2;
        int padX = kWidth / 2;

        Image<ChannelsNo> output(input.width, input.height);

        for (int y = 0; y < input.height; ++y) {
            for (int x = 0; x < input.width; ++x) {
                std::array<f32, ChannelsNo> acc = {0};

                for (int ky = 0; ky < kHeight; ++ky) {
                    for (int kx = 0; kx < kWidth; ++kx) {
                        int ix = x + kx - padX;
                        int iy = y + ky - padY;

                        if (ix >= 0 && ix < input.width && iy >= 0 && iy < input.height) {
                            auto pixel = input.at(ix, iy);
                            float coeff = kernel[ky][kx];
                            for (int c = 0; c < ChannelsNo; ++c)
                                acc[c] += pixel[c] * coeff;
                        }
                    }
                }

                auto& out = output.at(x, y);
                for (int c = 0; c < ChannelsNo; ++c)
                    out[c] = std::clamp<int>(acc[c], 0, 255);
            }
        }

        return output;
    }

}


#endif //KERNEL_IMAGE_PROCESSING_KERNEL_H
