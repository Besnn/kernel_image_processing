//
// Created by besnn on 7/29/25.
//

#ifndef NETPBM_IO_H
#define NETPBM_IO_H

#include "NetpbmImageFactory.h"

class NetPBM_IO {
public:
    NetPBM_IO() = delete;

    static PPM * readPPMfromFile(const std::string &path);
    static void writePPMtoFile(PPM * ppm, const std::string &path);
    static PGM * readPGMfromFile(const std::string &path);
    static void writePGMtoFile(PGM * pgm, const std::string &path);

private:
    static void skipComments(std::istream &is);
};

#endif //NETPBM_IO_H
