//
// Created by Besnik Nuro on 09/08/25.
//

#include <gtest/gtest.h>
#include <NetpbmImageFactory.h>

TEST(pgm_unit_tests, creates_pgm_with_zero_resolution) {
    auto pgm = NetpbmImageFactory::createPGM(0, 0);
    EXPECT_EQ(pgm->getWidth(), 0);
    EXPECT_EQ(pgm->getHeight(), 0);
    delete pgm;
}

TEST(pgm_unit_tests, creates_pgm_with_u32max_resolution) {
    auto pgm = NetpbmImageFactory::createPGM(UINT32_MAX, UINT32_MAX);
    EXPECT_EQ(pgm->getWidth(), UINT32_MAX);
    EXPECT_EQ(pgm->getHeight(), UINT32_MAX);
    delete pgm;
}

TEST(pgm_unit_tests, creates_pgm_with_correct_resolution) {
    auto pgm = NetpbmImageFactory::createPGM(1024, 768);
    EXPECT_EQ(pgm->getWidth(), 1024);
    EXPECT_EQ(pgm->getHeight(), 768);
    delete pgm;
}

TEST(pgm_unit_tests, creates_pgm_with_single_channel_and_its_gray) {
    auto pgm = NetpbmImageFactory::createPGM(0, 0);
    EXPECT_EQ(pgm->getChannels().size(), 1);
    auto gray_channel = pgm->getChannel("Gray");

    EXPECT_TRUE(gray_channel != nullptr);
    delete pgm;
}

TEST(pgm_unit_tests, creates_pgm_and_the_pixels_are_initialized_to_zero) {
    auto pgm = NetpbmImageFactory::createPGM(100, 100);
    auto gray_channel = pgm->getChannel("Gray");
    auto ch_size = gray_channel->size();
    flag all_zeros = true;
    for (u32 i = 0;i < ch_size; i++) {
        if ((*gray_channel)[i] != 0) all_zeros = false;
    }
    EXPECT_TRUE(all_zeros);
    delete pgm;
}

TEST(pgm_unit_tests, getting_nonexisting_channel_returns_nullptr) {
    auto pgm = NetpbmImageFactory::createPGM(0, 0);
    auto x_channel = pgm->getChannel("X");
    auto a_channel = pgm->getChannel("Alpha");
    EXPECT_TRUE(x_channel == nullptr);
    EXPECT_TRUE(a_channel == nullptr);
    delete pgm;
}