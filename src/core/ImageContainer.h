//
// Created by Besnik Nuro on 17/03/25.
//

#ifndef KERNEL_IMAGE_PROCESSING_IMAGECONTAINER_H
#define KERNEL_IMAGE_PROCESSING_IMAGECONTAINER_H

#include <memory>
#include <vector>

#include "types.h"
#include "image_formats/PNM.h"

class ImageContainer {
public:
    ImageContainer(u32 width, u32 height, std::unique_ptr<PNM> image);
    //NOTE: change pixelData to Image
    //NOTE: good job old me^
    ~ImageContainer();
private:
    u32 width;
    u32 height;
    std::unique_ptr<PNM> image;
};


#endif //KERNEL_IMAGE_PROCESSING_IMAGECONTAINER_H
