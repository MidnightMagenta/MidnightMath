#include "../include/vector.hpp"
#include <gtest/gtest.h>

TEST(VectorTests, vec2_add_test) {
	md_math::vec2 vec({1.f, 2.f});
	vec += vec;
	EXPECT_EQ(vec, md_math::vec2({2.f, 4.f}));
}

TEST(VectorTests, vec2_sub_test) {
	md_math::vec2 vec({1.f, 2.f});
	vec -= vec;
	EXPECT_EQ(vec, md_math::vec2({0.f, 0.f}));
}

TEST(VectorTests, vec2_mul_test) {
	md_math::vec2 vec({1.f, 2.f});
	vec *= vec;
	EXPECT_EQ(vec, md_math::vec2({1.f, 4.f}));
}

TEST(VectorTests, vec2_div_test) {
	md_math::vec2 vec({1.f, 2.f});
	vec /= vec;
	EXPECT_EQ(vec, md_math::vec2({1.f, 1.f}));
}