//
// Created by Besnik Nuro on 17/03/25.
//

#include "ImageContainer.h"

ImageContainer::ImageContainer(u32 width, u32 height, std::vector<u8> &pixelData)
: width(width), height(height), pixelData(pixelData) {}

ImageContainer::~ImageContainer() {

}
