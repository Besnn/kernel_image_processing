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

        Channel<T> * output = new Channel<T>(*channel);

        for (int y = 0; y < channel_height; ++y) {
            for (int x = 0; x < channel_width; ++x) {
                f32 acc = 0.f;

                for (int ky = 0; ky < k_height; ++ky) {
                    for (int kx = 0; kx < k_width; ++kx) {
                        int ix = x + kx - x_padding;
                        int iy = y + ky - y_padding;

                        if (ix >= 0 && ix < channel_width && iy >= 0 && iy < channel_height) {
                                acc += (*channel)[ix + channel_width * iy] * kernel->kernel[ky][kx];
                        }
                    }
                }
                int output_index = y * channel_width + x;
                (*output)[output_index] = static_cast<T>(std::clamp(acc, 0.f, 255.f));
            }
        }

        return output;
    }


    template<u8 channel_num, typename T>
    static MultiChannelImage<channel_num, T> * apply(MultiChannelImage<channel_num, T> * input,
    const Kernel * kernel)
    {
        std::map<std::string, Channel<T> *> new_channels;

        Channel<T> * new_channel = nullptr;

        for (const auto [key, channel] : input->getChannels()) {
            new_channel = apply(channel, input->getHeight(), input->getWidth(), kernel);
            new_channels.emplace(key, new_channel);
        }

        for (const auto [key, channel] : new_channels) {
            input->setChannel(key, channel);
        }
        return input;
    }
}



#endif //KERNEL_IMAGE_PROCESSING_KERNEL_H
