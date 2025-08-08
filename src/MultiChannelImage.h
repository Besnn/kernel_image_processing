//
// Created by besnn on 7/29/25.
//

#ifndef MULTICHANNELIMAGE_H
#define MULTICHANNELIMAGE_H

#include <map>
#include <memory>
#include <vector>
#include <iostream>


#include "types.h"

template <typename T>
using Channel = std::vector<T>;

template <u8 channel_num, typename T>
class MultiChannelImage {
public:
    MultiChannelImage(u32 width, u32 height);
private:
    u32 width, height;
    std::map<std::string, Channel<T> * > channels;

private:
    ~MultiChannelImage();
};


template<u8 channel_num, typename T>
MultiChannelImage<channel_num, T>::MultiChannelImage(u32 width, u32 height)
: width(width), height(height)
{
    //TODO: see what's to be added
    this->channels = std::map<std::string, Channel<T> * >();

    auto RChannel = new Channel<T>(width * height);
    auto GChannel = new Channel<T>(width * height);
    auto BChannel = new Channel<T>(width * height);

    this->channels.emplace("R", std::move(RChannel));
    this->channels.emplace("G", std::move(GChannel));
    this->channels.emplace("B", std::move(BChannel));
}




#endif //MULTICHANNELIMAGE_H
