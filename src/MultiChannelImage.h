//
// Created by besnn on 7/29/25.
//

#ifndef MULTICHANNELIMAGE_H
#define MULTICHANNELIMAGE_H

#include <map>
#include <memory>
#include <vector>

#include "types.h"

template <typename T>
using Channel = std::vector<T>;

template <u8 channel_num, typename T>
class MultiChannelImage {
public:
    MultiChannelImage(u32 width, u32 height);
private:
    u32 width, height;
    std::map<std::string, Channel<T>> & channels;
};

//TODO: ???
template<u8 channelNo, typename T>
MultiChannelImage<channel_num, T>::MultiChannelImage(u32 width, u32 height) : width(width), height(height) {}




#endif //MULTICHANNELIMAGE_H
