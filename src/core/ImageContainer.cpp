//
// Created by Besnik Nuro on 17/03/25.
//

#include "ImageContainer.h"

ImageContainer::ImageContainer(u32 width, u32 height, std::unique_ptr<PNM> image) : width(width), height(height), image(std::move(image)) {}

ImageContainer::~ImageContainer() {

}
