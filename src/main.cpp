#include <iostream>

#include "src/codecs/PBMCodec.h"

int main() {
    auto pbm = new PBM(10, 10, P4);

    delete pbm;
    return 0;
}
