//
// Created by Besnik Nuro on 17/03/25.
//
#include <iostream>

#include "PBM.h"
#include "src/core/types.h"

PBM::PBM(u32 width, u32 height, PNMMagicNumber magicNumber) {
    if (magicNumber != PNMMagicNumber::Undefined)
        this->magicNumber = magicNumber;
    else throw std::runtime_error("PNM image's magic number unknown/undefined.");

    this->width = width;
    this->height = height;

    auto bitmap = new std::vector<bool>(width * height, false);
    auto channel = new Channel(*bitmap);
    this->channels = std::unique_ptr<ChannelContainer>(new ChannelContainer(1, *channel));
    delete bitmap;
    delete channel;
    // bitmap->resize(width * height);
}

PBM::~PBM() {
    // delete[] this->
}