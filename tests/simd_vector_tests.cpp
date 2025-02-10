#include "../include/vector.hpp"
#include <gtest/gtest.h>

#define TEST_SIGNATURE_4D_SIMD(test_name) TEST(Vec4SimdTest, test_name)
#define TEST_SIGNATURE_2D_DSIMD(test_name) TEST(DVec2SimdTest, test_name)
#define TEST_SIGNATURE_4D_DSIMD(test_name) TEST(DVec4SimdTest, test_name)

#define VEC_OP_TEST_4D_SIMD(op, test_name)                                     \
	TEST_SIGNATURE_4D_SIMD(test_name) {                                        \
		float x = 1.0f, y = 2.0f, z = 3.0f, w = 4.0f;                          \
		md_math::vec4_v vec(x, y, z, w);                                       \
		vec = vec op vec;                                                      \
		EXPECT_EQ(vec.x(), x op x);                                            \
		EXPECT_EQ(vec.y(), y op y);                                            \
		EXPECT_EQ(vec.z(), z op z);                                            \
		EXPECT_EQ(vec.w(), w op w);                                            \
	}

#define VEC_OP_TEST_2D_DSIMD(op, test_name)                                    \
	TEST_SIGNATURE_2D_DSIMD(test_name) {                                       \
		double x = 1.0, y = 2.0;                                               \
		md_math::dvec2_v vec(x, y);                                            \
		vec = vec op vec;                                                      \
		EXPECT_EQ(vec.x(), x op x);                                            \
		EXPECT_EQ(vec.y(), y op y);                                            \
	}

#define VEC_OP_TEST_4D_DSIMD(op, test_name)                                    \
	TEST_SIGNATURE_4D_DSIMD(test_name) {                                       \
		double x = 1.0, y = 2.0, z = 3.0, w = 4.0;                             \
		md_math::dvec4_v vec(x, y, z, w);                                      \
		vec = vec op vec;                                                      \
		EXPECT_EQ(vec.x(), x op x);                                            \
		EXPECT_EQ(vec.y(), y op y);                                            \
		EXPECT_EQ(vec.z(), z op z);                                            \
		EXPECT_EQ(vec.w(), w op w);                                            \
	}

VEC_OP_TEST_4D_SIMD(+, add_test)
VEC_OP_TEST_4D_SIMD(-, sub_test)
VEC_OP_TEST_4D_SIMD(*, mul_test)
VEC_OP_TEST_4D_SIMD(/, div_test)

VEC_OP_TEST_2D_DSIMD(+, add_test)
VEC_OP_TEST_2D_DSIMD(-, sub_test)
VEC_OP_TEST_2D_DSIMD(*, mul_test)
VEC_OP_TEST_2D_DSIMD(/, div_test)

VEC_OP_TEST_4D_DSIMD(+, add_test)
VEC_OP_TEST_4D_DSIMD(-, sub_test)
VEC_OP_TEST_4D_DSIMD(*, mul_test)
VEC_OP_TEST_4D_DSIMD(/, div_test)

TEST_SIGNATURE_4D_SIMD(magnitude_test) {
	float x = 1.0f, y = 2.0f, z = 3.0f, w = 4.0f;
	md_math::vec4_v vec(x, y, z, w);
	EXPECT_NEAR(vec.magnitude(), std::sqrt(x * x + y * y + z * z + w * w),
				1e-5);
	vec.normalize();
	EXPECT_NEAR(vec.magnitude(), 1.0f, 1e-5);
}

TEST_SIGNATURE_2D_DSIMD(magnitude_test) {
	double x = 1.0, y = 2.0;
	md_math::dvec2_v vec(x, y);
	EXPECT_NEAR(vec.magnitude(), std::sqrt(x * x + y * y), 1e-5);
	vec.normalize();
	EXPECT_NEAR(vec.magnitude(), 1.0, 1e-5);
}

TEST_SIGNATURE_4D_DSIMD(magnitude_test) {
	double x = 1.0, y = 2.0, z = 3.0, w = 4.0;
	md_math::dvec4_v vec(x, y, z, w);
	EXPECT_NEAR(vec.magnitude(), std::sqrt(x * x + y * y + z * z + w * w),
				1e-5);
	vec.normalize();
	EXPECT_NEAR(vec.magnitude(), 1.0, 1e-5);
}

TEST_SIGNATURE_4D_SIMD(dot_test) {
	float x = 1.0f, y = 2.0f, z = 3.0f, w = 4.0f;
	md_math::vec4_v vec1(x, y, z, w);
	md_math::vec4_v vec2(x, y, z, w);
	EXPECT_EQ(vec1.dot(vec2), x * x + y * y + z * z + w * w);
}

TEST_SIGNATURE_2D_DSIMD(dot_test) {
	double x = 1.0, y = 2.0;
	md_math::dvec2_v vec1(x, y);
	md_math::dvec2_v vec2(x, y);
	EXPECT_EQ(vec1.dot(vec2), x * x + y * y);
}

TEST_SIGNATURE_4D_DSIMD(dot_test) {
	double x = 1.0, y = 2.0, z = 3.0, w = 4.0;
	md_math::dvec4_v vec1(x, y, z, w);
	md_math::dvec4_v vec2(x, y, z, w);
	EXPECT_EQ(vec1.dot(vec2), x * x + y * y + z * z + w * w);
}
