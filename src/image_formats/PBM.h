//
// Created by Besnik Nuro on 17/03/25.
//

#ifndef KERNEL_IMAGE_PROCESSING_PBM_H
#define KERNEL_IMAGE_PROCESSING_PBM_H

//TODO: fix

#include "PNM.h"

class PBM : PNM {
public:
    PBM(u32 width, u32 height, PNMMagicNumber magicNumber);
    ~PBM();
    //NOTE: tweak implementation
};
#endif //KERNEL_IMAGE_PROCESSING_PBM_H
