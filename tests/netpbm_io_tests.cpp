//
// Created by besnn on 10/5/2025.
//

#include <gtest/gtest.h>
#include "NetPBM_IO.h"
#include "test_utilities.hpp"

TEST(netpbm_io_unit_tests,
     reading_and_writing_the_same_p6_ppm_results_in_an_identical_copy)
     {
    std::string P6_PPM_FILE = "../examples/p6_example_0.ppm";
    std::string _P6_PPM_FILE_COPY = "../tmp/netpbm_io_p6_test.ppm";
      auto ppm = NetPBM_IO::readPPMfromFile(P6_PPM_FILE);
      NetPBM_IO::writePPMtoFile(ppm, _P6_PPM_FILE_COPY);
      bool are_equal = TEST_HELPER::files_are_identical(P6_PPM_FILE,
                                       _P6_PPM_FILE_COPY);
      EXPECT_TRUE(are_equal);
      delete ppm;
}

TEST(netpbm_io_unit_tests,
     reading_and_writing_the_same_p5_pgm_results_in_an_identical_copy)
{
    std::string P5_PGM_FILE = "../examples/p5_example_1.pgm";
    std::string _P5_PGM_FILE_COPY = "../tmp/netpbm_io_p5_test.pgm";
  auto pgm = NetPBM_IO::readPGMfromFile(P5_PGM_FILE);
  NetPBM_IO::writePGMtoFile(pgm, _P5_PGM_FILE_COPY);
  bool are_equal = TEST_HELPER::files_are_identical(P5_PGM_FILE,
                                                    _P5_PGM_FILE_COPY);
  EXPECT_TRUE(are_equal);
  delete pgm;
}

TEST(netpbm_io_unit_tests,
     reading_and_writing_the_same_p4_pbm_results_in_an_identical_copy)
{
    std::string P4_PBM_FILE = "../examples/p4_example_0.pbm";
    std::string _P4_PBM_FILE_COPY = "../tmp/netpbm_io_p4_test.pbm";
  auto pbm = NetPBM_IO::readPBMfromFile(P4_PBM_FILE);
  NetPBM_IO::writePBMtoFile(pbm, _P4_PBM_FILE_COPY);
  bool are_equal = TEST_HELPER::files_are_identical(P4_PBM_FILE,
                                                    _P4_PBM_FILE_COPY);
  EXPECT_TRUE(are_equal);
  delete pbm;
}

TEST(netpbm_io_unit_tests,
     reading_and_writing_the_same_p3_ppm_results_in_an_identical_copy)
{
    std::string P3_PPM_FILE = "../examples/p3_example_sprite.ppm";
    std::string _P3_PPM_FILE_COPY = "../tmp/netpbm_io_p3_test.ppm";
    auto ppm = NetPBM_IO::readPPMfromFile(P3_PPM_FILE);
    NetPBM_IO::writePPMtoFile(ppm, _P3_PPM_FILE_COPY);
    bool are_equal = TEST_HELPER::equalNetpbmTextFiles(P3_PPM_FILE, _P3_PPM_FILE_COPY);
    EXPECT_TRUE(are_equal);
    delete ppm;
}

TEST(netpbm_io_unit_tests,
     reading_and_writing_the_same_p2_pgm_results_in_an_identical_copy)
{
    std::string P2_PGM_FILE = "../examples/p2_example_3.pgm";
    std::string _P2_PGM_FILE_COPY = "../tmp/netpbm_io_p2_test.pgm";
    auto pgm = NetPBM_IO::readPGMfromFile(P2_PGM_FILE);
    NetPBM_IO::writePGMtoFile(pgm, _P2_PGM_FILE_COPY);
    bool are_equal = TEST_HELPER::equalNetpbmTextFiles(P2_PGM_FILE, _P2_PGM_FILE_COPY);
    EXPECT_TRUE(are_equal);
    delete pgm;
}

TEST(netpbm_io_unit_tests,
     reading_and_writing_the_same_p1_pbm_results_in_an_identical_copy)
{
    std::string P1_PBM_FILE = "../examples/p1_example_a.pbm";
    std::string _P1_PBM_FILE_COPY = "../tmp/netpbm_io_p1_test.pbm";
    auto pbm = NetPBM_IO::readPBMfromFile(P1_PBM_FILE);
    NetPBM_IO::writePBMtoFile(pbm, _P1_PBM_FILE_COPY);
    bool are_equal = TEST_HELPER::equalNetpbmTextFiles(P1_PBM_FILE, _P1_PBM_FILE_COPY);
    EXPECT_TRUE(are_equal);
    delete pbm;
}