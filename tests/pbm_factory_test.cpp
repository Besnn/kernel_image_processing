//
// Created by Besnik Nuro on 09/08/25.
//

#include <gtest/gtest.h>
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
    auto ppm = NetpbmImageFactory::createPPM(0, 0);
    EXPECT_EQ(ppm->getChannels().size(), 3);
    auto r_channel = ppm->getChannel("R");
    auto g_channel = ppm->getChannel("G");
    auto b_channel = ppm->getChannel("B");

    EXPECT_TRUE(r_channel != nullptr);
    EXPECT_TRUE(g_channel != nullptr);
    EXPECT_TRUE(b_channel != nullptr);
}

TEST(ppm_unit_tests, getting_nonexisting_channel_returns_nullptr) {
    auto ppm = NetpbmImageFactory::createPPM(0, 0);
    auto x_channel = ppm->getChannel("X");
    auto a_channel = ppm->getChannel("Alpha");
    EXPECT_TRUE(x_channel == nullptr);
    EXPECT_TRUE(a_channel == nullptr);
}