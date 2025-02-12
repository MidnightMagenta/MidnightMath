#include <gtest/gtest.h>
#include "../include/support_functions.hpp"

TEST(SanityTest, SanityTest) { EXPECT_EQ(1 + 1, 2); }
TEST(AVX_SupportTest, AVX_SupportTest) { EXPECT_TRUE(md_math::support::CheckSIMD_Support()); }