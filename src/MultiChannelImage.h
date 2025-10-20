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
    MultiChannelImage(u32 width, u32 height, std::vector<std::string> channel_keys);
private:
    std::string file_signature;
    u32 width, height;
    std::map<std::string, Channel<T> *> channels;

public:
    Channel<T> * getChannel(const std::string &key) {
        auto iter = this->channels.find(key);
        if (iter != this->channels.end()) {
            return iter->second;
        } else return nullptr;
    }

    void setChannel(const std::string key, Channel<T> * channel) {
        auto iter = this->channels.find(key);
        if (iter != this->channels.end()) {
            delete iter->second;
            iter->second = channel;
        }
    }

    const std::map<std::string, Channel<T> *> getChannels() const {
        return channels;
    }

    u32 getHeight() const {
        return height;
    }

    void setHeight(u32 height) {
        MultiChannelImage::height = height;
        for (const auto& [name, channel_ptr] : this->channels) {
            channel_ptr->resize(width * height);
        }
    }

    u32 getWidth() const {
        return width;
    }

    void setWidth(u32 width) {
        MultiChannelImage::width = width;
        for (const auto& [name, channel_ptr] : this->channels) {
            channel_ptr->resize(width * height);
        }
    }

    const std::string &getFileSignature() const {
        return file_signature;
    }

    void setFileSignature(const std::string &fileSignature) {
        file_signature = fileSignature;
    }

public:
    ~MultiChannelImage();
};


template<u8 channel_num, typename T>
MultiChannelImage<channel_num, T>::MultiChannelImage(u32 width, u32 height,
                                                     const std::vector<std::string> channel_keys)
: width(width), height(height), file_signature("\0")
{
    if (channel_keys.size() < channel_num)
        throw std::runtime_error("List of channel keys is shorter than expected.");

    this->channels = std::map<std::string, Channel<T> * >();

    Channel<T> * channel;
    for (u8 i = 0; i < channel_num; i++) {
        channel = new Channel<T>(width * height);
        this->channels.emplace(channel_keys[i], channel);
    }
}

template<u8 channel_num, typename T>
MultiChannelImage<channel_num, T>::~MultiChannelImage() {
    for (auto const& [key, channel_ptr] : this->channels) {
        delete channel_ptr;
    }
}

#endif //MULTICHANNELIMAGE_H
