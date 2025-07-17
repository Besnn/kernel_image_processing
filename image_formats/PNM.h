//
// Created by Besnik Nuro on 17/03/25.
//

#ifndef KERNEL_IMAGE_PROCESSING_PNM_H
#define KERNEL_IMAGE_PROCESSING_PNM_H

#include <vector>
#include <variant>

#include "../core/types.h"
enum PNMMagicNumber {
    P1, P2, P3, P4, P5, P6, P7, Undefined
};
//NOTE: for now implement only P4-P6
//NOTE: first P4

using Channel = std::variant<std::vector<bool>, std::vector<char>, std::vector<u16>>;
using ChannelContainer = std::vector<Channel>;
class PNM {
    //NOTE: change from public to protected/private and make codec friend class
    friend class PBMCodec;
public:
    PNM(u32 width, u32 height, PNMMagicNumber magicNumber, ChannelContainer channels);
protected:
    PNMMagicNumber magicNumber;
    //NOTE: why did I make this protected? change to private maybe?
private:
    u32 width;
    u32 height;
    ChannelContainer channels;
};


#endif //KERNEL_IMAGE_PROCESSING_PNM_H
