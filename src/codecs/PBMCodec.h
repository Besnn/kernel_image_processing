//
// Created by Besnik Nuro on 17/03/25.
//

#ifndef KERNEL_IMAGE_PROCESSING_PBMCODEC_H
#define KERNEL_IMAGE_PROCESSING_PBMCODEC_H

#include <string>
#include "../core/ImageContainer.h"
#include "../image_formats/PNM.h"
#include "../image_formats/PBM.h"
//#include "../image_formats/PGM.h"

class PBMCodec {
public:
    static ImageContainer loadFromFile(const std::string& filename);
    static void saveToFile(const std::string& filename);
};


#endif //KERNEL_IMAGE_PROCESSING_PBMCODEC_H
