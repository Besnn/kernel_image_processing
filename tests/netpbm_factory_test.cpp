//
// Created by Besnik Nuro on 09/08/25.
//

#include <gtest/gtest.h>
#include <limits.h>
#include <NetpbmImageFactory.h>

TEST(ppm_unit_tests, creates_ppm_with_zero_resolution) {
    auto ppm = NetpbmImageFactory::createPPM(0, 0);
    EXPECT_EQ(ppm->getWidth(), 0);
    EXPECT_EQ(ppm->getHeight(), 0);
}

TEST(ppm_unit_tests, creates_ppm_with_u32max_resolution) {
    auto ppm = NetpbmImageFactory::createPPM(UINT32_MAX, UINT32_MAX);
    EXPECT_EQ(ppm->getWidth(), UINT32_MAX);
    EXPECT_EQ(ppm->getHeight(), UINT32_MAX);
}

TEST(ppm_unit_tests, creates_ppm_with_three_channels_and_theyre_RGB) {
    auto ppm = NetpbmImageFactory::createPPM(100, 100);
    auto channels = ppm->getChannels();
    auto r_channel = channels.find("R");
    auto g_channel = channels.find("G");

}