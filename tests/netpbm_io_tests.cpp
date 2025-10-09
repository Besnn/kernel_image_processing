//
// Created by besnn on 10/5/2025.
//

#include <gtest/gtest.h>
#include "NetPBM_IO.h"
#include "test_utilities.hpp"

TEST(netpbm_io_unit_tests,
     reading_and_writing_the_same_ppm_results_in_an_identical_copy)
     {
      auto ppm = NetPBM_IO::readPPMfromFile("../examples/example_0.ppm");
      NetPBM_IO::writePPMtoFile(ppm, "../tmp/netpbm_io_ppm_test.ppm");
      bool are_equal = TEST_HELPER::files_are_identical("../examples/example_0.ppm",
                                       "../tmp/netpbm_io_ppm_test.ppm");
      EXPECT_TRUE(are_equal);
      delete ppm;
}

TEST(netpbm_io_unit_tests,
     reading_and_writing_the_same_pgm_results_in_an_identical_copy)
{
  auto pgm = NetPBM_IO::readPGMfromFile("../examples/11zon_example_1.pgm");
  NetPBM_IO::writePGMtoFile(pgm, "../tmp/netpbm_io_ppm_test.pgm");
  bool are_equal = TEST_HELPER::files_are_identical("../examples/11zon_example_1.pgm",
                                                    "../tmp/netpbm_io_ppm_test.pgm");
  EXPECT_TRUE(are_equal);
  delete pgm;
}

TEST(netpbm_io_unit_tests,
     reading_and_writing_the_same_pbm_results_in_an_identical_copy)
{
  auto pbm = NetPBM_IO::readPBMfromFile("../examples/example_0.pbm");
  NetPBM_IO::writePBMtoFile(pbm, "../tmp/netpbm_io_ppm_test.pbm");
  bool are_equal = TEST_HELPER::files_are_identical("../examples/example_0.pbm",
                                                    "../tmp/netpbm_io_ppm_test.pbm");
  EXPECT_TRUE(are_equal);
  delete pbm;
}