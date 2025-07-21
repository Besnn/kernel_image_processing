//
// Created by Besnik Nuro on 17/03/25.
//

#include "PNM.h"

PNM::PNM() {};

PNM::PNM(u32 width, u32 height, PNMMagicNumber magicNumber, std::unique_ptr<ChannelContainer> channels)
    : width(width), height(height), magicNumber(magicNumber), channels(std::move(channels)) {}