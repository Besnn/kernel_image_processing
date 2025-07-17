//
// Created by Besnik Nuro on 17/03/25.
//

#ifndef KERNEL_IMAGE_PROCESSING_IMAGECONTAINER_H
#define KERNEL_IMAGE_PROCESSING_IMAGECONTAINER_H

#include <vector>

#include "types.h"

class ImageContainer {
public:
    ImageContainer(u32 width, u32 height, std::vector<u8> &pixelData);
    //NOTE: change pixelData to Image
    ~ImageContainer();
private:
    u32 width;
    u32 height;
    std::vector<u8> & pixelData;
};


#endif //KERNEL_IMAGE_PROCESSING_IMAGECONTAINER_H
