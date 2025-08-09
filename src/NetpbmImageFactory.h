//
// Created by Besnik Nuro on 08/08/25.
//

#ifndef KERNEL_IMAGE_PROCESSING_NETPBMIMAGEFACTORY_H
#define KERNEL_IMAGE_PROCESSING_NETPBMIMAGEFACTORY_H

#include "types.h"
#include "MultiChannelImage.h"

using PBM = MultiChannelImage<1, bool>;
using PGM = MultiChannelImage<1, u16>;
using PPM = MultiChannelImage<3, u16>;

class NetpbmImageFactory {
public:
    static std::unique_ptr<PPM> createPPM(u32 width, u32 height);
    static std::unique_ptr<PGM> createPGM(u32 width, u32 height);
};


#endif //KERNEL_IMAGE_PROCESSING_NETPBMIMAGEFACTORY_H
