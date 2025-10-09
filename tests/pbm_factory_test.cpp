//
// Created by Besnik Nuro on 09/08/25.
//

#include <gtest/gtest.h>
#include <NetpbmImageFactory.h>

TEST(pbm_unit_tests, creates_pbm_with_zero_resolution) {
    auto pbm = NetpbmImageFactory::createPBM(0, 0);
    EXPECT_EQ(pbm->getWidth(), 0);
    EXPECT_EQ(pbm->getHeight(), 0);
    delete pbm;
}

TEST(pbm_unit_tests, creates_pbm_with_u32max_resolution) {
    auto pbm = NetpbmImageFactory::createPBM(UINT32_MAX, UINT32_MAX);
    EXPECT_EQ(pbm->getWidth(), UINT32_MAX);
    EXPECT_EQ(pbm->getHeight(), UINT32_MAX);
    delete pbm;
}

TEST(pbm_unit_tests, creates_pbm_with_correct_resolution) {
    auto pbm = NetpbmImageFactory::createPBM(1024, 768);
    EXPECT_EQ(pbm->getWidth(), 1024);
    EXPECT_EQ(pbm->getHeight(), 768);
    delete pbm;
}

TEST(pbm_unit_tests, creates_pbm_with_single_channel_and_its_bw) {
    auto pbm = NetpbmImageFactory::createPBM(0, 0);
    EXPECT_EQ(pbm->getChannels().size(), 1);
    auto bw_channel = pbm->getChannel("BW");

    EXPECT_TRUE(bw_channel != nullptr);
    delete pbm;
}

TEST(pbm_unit_tests, creates_pbm_and_the_pixels_are_initialized_to_zero) {
    auto pbm = NetpbmImageFactory::createPBM(100, 100);
    auto bw_channel = pbm->getChannel("BW");
    auto ch_size = bw_channel->size();
    flag all_zeros = true;
    for (u32 i = 0;i < ch_size; i++) {
        if ((*bw_channel)[i] != 0) all_zeros = false;
    }
    EXPECT_TRUE(all_zeros);
    delete pbm;
}

TEST(pbm_unit_tests, getting_nonexisting_channel_returns_nullptr) {
    auto pbm = NetpbmImageFactory::createPBM(0, 0);
    auto x_channel = pbm->getChannel("X");
    auto a_channel = pbm->getChannel("Alpha");
    EXPECT_TRUE(x_channel == nullptr);
    EXPECT_TRUE(a_channel == nullptr);
    delete pbm;
}

TEST(pbm_unit_tests, setting_height_resizes_channels) {
    auto pbm = NetpbmImageFactory::createPBM(20, 20);
    pbm->setHeight(100);
    EXPECT_EQ(pbm->getHeight(), 100);
    auto bw_channel = pbm->getChannel("BW");
    EXPECT_EQ(bw_channel->size(), 20 * 100);
    delete pbm;
}

TEST(pbm_unit_tests, setting_width_resizes_channels) {
    auto pbm = NetpbmImageFactory::createPBM(20, 20);
    pbm->setWidth(100);
    EXPECT_EQ(pbm->getWidth(), 100);
    auto bw_channel = pbm->getChannel("BW");
    EXPECT_EQ(bw_channel->size(), 20 * 100);
    delete pbm;
}