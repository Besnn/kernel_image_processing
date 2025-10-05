//
// Created by Besnik Nuro on 09/08/25.
//

#include <gtest/gtest.h>
#include <NetpbmImageFactory.h>

TEST(ppm_unit_tests, creates_ppm_with_zero_resolution) {
    auto ppm = NetpbmImageFactory::createPPM(0, 0);
    EXPECT_EQ(ppm->getWidth(), 0);
    EXPECT_EQ(ppm->getHeight(), 0);
    delete ppm;
}

TEST(ppm_unit_tests, creates_ppm_with_u32max_resolution) {
    auto ppm = NetpbmImageFactory::createPPM(UINT32_MAX, UINT32_MAX);
    EXPECT_EQ(ppm->getWidth(), UINT32_MAX);
    EXPECT_EQ(ppm->getHeight(), UINT32_MAX);
    delete ppm;
}

TEST(ppm_unit_tests, creates_ppm_with_correct_resolution) {
    auto ppm = NetpbmImageFactory::createPPM(1024, 768);
    EXPECT_EQ(ppm->getWidth(), 1024);
    EXPECT_EQ(ppm->getHeight(), 768);
    delete ppm;
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
    delete ppm;
}

TEST(ppm_unit_tests, creates_ppm_and_the_channels_are_initialized_with_zeros) {
    auto ppm = NetpbmImageFactory::createPPM(100, 100);
    auto r_channel = ppm->getChannel("R");
    auto ch_size = r_channel->size();
    flag all_zeros = true;
    for (u32 i = 0;i < ch_size; i++) {
        if ((*r_channel)[i] != 0) all_zeros = false;
    }
    auto g_channel = ppm->getChannel("G");
    for (u32 i = 0;i < ch_size; i++) {
        if ((*g_channel)[i] != 0) all_zeros = false;
    }
    auto b_channel = ppm->getChannel("B");
    for (u32 i = 0;i < ch_size; i++) {
        if ((*b_channel)[i] != 0) all_zeros = false;
    }
    EXPECT_TRUE(all_zeros);
    delete ppm;
}

TEST(ppm_unit_tests, getting_nonexisting_channel_returns_nullptr) {
    auto ppm = NetpbmImageFactory::createPPM(0, 0);
    auto x_channel = ppm->getChannel("X");
    auto a_channel = ppm->getChannel("Alpha");
    EXPECT_TRUE(x_channel == nullptr);
    EXPECT_TRUE(a_channel == nullptr);
    delete ppm;
}

TEST(ppm_unit_tests, setting_height_resizes_channels) {
    auto ppm = NetpbmImageFactory::createPPM(20, 20);
    ppm->setHeight(100);
    EXPECT_EQ(ppm->getHeight(), 100);
    auto r_channel = ppm->getChannel("R");
    EXPECT_EQ(r_channel->size(), 20 * 100);
    auto g_channel = ppm->getChannel("G");
    EXPECT_EQ(g_channel->size(), 20 * 100);
    auto b_channel = ppm->getChannel("B");
    EXPECT_EQ(b_channel->size(), 20 * 100);
    delete ppm;
}

TEST(ppm_unit_tests, setting_width_resizes_channels) {
    auto ppm = NetpbmImageFactory::createPPM(20, 20);
    ppm->setWidth(100);
    EXPECT_EQ(ppm->getWidth(), 100);
    auto r_channel = ppm->getChannel("R");
    EXPECT_EQ(r_channel->size(), 20 * 100);
    auto g_channel = ppm->getChannel("G");
    EXPECT_EQ(g_channel->size(), 20 * 100);
    auto b_channel = ppm->getChannel("B");
    EXPECT_EQ(b_channel->size(), 20 * 100);
    delete ppm;
}
