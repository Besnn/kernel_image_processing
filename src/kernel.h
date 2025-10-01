//
// Created by Besnik Nuro on 17/03/25.
//

#ifndef KERNEL_IMAGE_PROCESSING_KERNEL_H
#define KERNEL_IMAGE_PROCESSING_KERNEL_H

#include <algorithm>
#include <iostream>

#include "types.h"
#include "MultiChannelImage.h"

namespace Kernel {

    //TODO: implement kernel
    struct Kernel {
    public:
        u32 height;
        u32 width;
        std::vector<std::vector<f32>> kernel;
    };

    template<typename T>
    static Channel<T> * apply(Channel<T> * channel, u32 channel_height, u32 channel_width, const Kernel * kernel) {
        int k_height = kernel->height;
        int k_width = kernel->width;
        int y_padding = k_height / 2;
        int x_padding = k_width / 2;

        //FIXME: how do I fucking copy this vector of vectors toasdasdas`d asd
        Channel<T> * output = new Channel<T>(*channel);

        for (int y = 0; y < channel_height; ++y) {
            for (int x = 0; x < channel_width; ++x) {
                f32 acc = 0.f;

                for (int ky = 0; ky < k_height; ++ky) {
                    for (int kx = 0; kx < k_width; ++kx) {
                        int ix = x + kx - x_padding;
                        int iy = y + ky - y_padding;
                        //FIXME: 1 Oct 2025 --- EXC_BAD_ACCESS
                        if (ix >= 0 && ix < channel_width && iy >= 0 && iy < channel_height) {
                                acc += (*channel)[ix + channel_width * iy] * kernel->kernel[ky][kx];
//                                std::cout << "channel[" << iy << "][" << ix << "] = " << int((*channel)[ix + channel_width * iy])
//                                      << ", kernel = " << kernel->kernel[ky][kx] << "\n";
                        }
                    }
                }
                int output_index = y * channel_width + x;
                (*output)[output_index] = static_cast<T>(std::clamp(acc, 0.f, 255.f));
//                std::cout << "acc = " << acc << " at (" << y << ", " << x << ")\n";
            }
        }

        return output;
    }


    //TODO: rewrite
    //NOTE: this code almost doesn't make sense because of the API
    template<u8 channel_num, typename T>
    static MultiChannelImage<channel_num, T> * apply(
        const MultiChannelImage<channel_num, T> * input,
        const std::vector<std::vector<f32>>& kernel
    ) {
        int k_height = kernel.size();
        int k_width = kernel[0].size();
        int pad_y = k_height / 2;
        int pad_x = k_width / 2;
        int ch_height = input->getHeight();
        int ch_width = input->getWidth();
        std::vector<std::string> channel_keys;
        channel_keys.resize(channel_num);
        auto channels = input->getChannels();
        for (const auto& [key, _] : channels) {
            channel_keys.push_back(key);
        }

        auto output = new MultiChannelImage<channel_num, T>(ch_width, ch_height, channel_keys);

        for (int y = 0; y < ch_height; ++y) {
            for (int x = 0; x < ch_width; ++x) {
                std::array<f32, channel_num> acc = {0};

                for (int ky = 0; ky < k_height; ++ky) {
                    for (int kx = 0; kx < k_width; ++kx) {
                        int ix = x + kx - pad_x;
                        int iy = y + ky - pad_y;

                        if (ix >= 0 && ix < ch_width && iy >= 0 && iy < ch_height) {
                            const auto& pixel = input->at(ix, iy);
                            float coeff = kernel[ky][kx];
                            for (int c = 0; c < channel_num; ++c) {
                                acc[c] += pixel[c] * coeff;
                            }
                        }
                    }
                }

                auto& out = output.at(x, y);
                for (int c = 0; c < channel_num; ++c) {
                    out[c] = static_cast<T>(std::clamp(acc[c], 0.f, 255.f));
                }
            }
        }

        return output;
    }
}



#endif //KERNEL_IMAGE_PROCESSING_KERNEL_H
