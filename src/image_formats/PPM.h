//
// Created by Besnik Nuro on 17/03/25.
//

#ifndef KERNEL_IMAGE_PROCESSING_PPM_H
#define KERNEL_IMAGE_PROCESSING_PPM_H

#include "PNM.h"

class PPM : PNM {
public:
    PPM(u32 width, u32 height);
    ~PPM();
};


#endif //KERNEL_IMAGE_PROCESSING_PPM_H
