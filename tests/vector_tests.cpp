#include "../include/vector.hpp"
#include <gtest/gtest.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923
#endif

#define TEST_SIGNATURE_2D(test_name) TEST(Vec2Test, test_name)
#define TEST_SIGNATURE_3D(test_name) TEST(Vec3Test, test_name)
#define TEST_SIGNATURE_4D(test_name) TEST(Vec4Test, test_name)

#define VEC_OP_TEST_2D(op, test_name)                                          \
	TEST_SIGNATURE_2D(test_name) {                                             \
		srand(time(0));                                                        \
		float x = (float) (rand() % 100), y = (float) (rand() % 100);          \
		md_math::vec2_s vec({x, y});                                           \
		vec = vec op vec;                                                      \
		md_math::vec2_s expected1({x op x, y op y});                           \
		EXPECT_NEAR(vec.x(), expected1.x(), 1e-5);                             \
		EXPECT_NEAR(vec.y(), expected1.y(), 1e-5);                             \
		vec = {x, y};                                                          \
		vec = vec op md_math::vec2_s({1, 1});                                  \
		md_math::vec2_s expected2({x op 1, y op 1});                           \
		EXPECT_NEAR(vec.x(), expected2.x(), 1e-5);                             \
		EXPECT_NEAR(vec.y(), expected2.y(), 1e-5);                             \
	}

#define VEC_OP_TEST_3D(op, test_name)                                          \
	TEST_SIGNATURE_3D(test_name) {                                             \
		srand(time(0));                                                        \
		float x = (float) (rand() % 100), y = (float) (rand() % 100),          \
			  z = (float) (rand() % 100);                                      \
		md_math::vec3_s vec({x, y, z});                                        \
		vec = vec op vec;                                                      \
		md_math::vec3_s expected1({x op x, y op y, z op z});                   \
		EXPECT_NEAR(vec.x(), expected1.x(), 1e-5);                             \
		EXPECT_NEAR(vec.y(), expected1.y(), 1e-5);                             \
		EXPECT_NEAR(vec.z(), expected1.z(), 1e-5);                             \
		vec = {x, y, z};                                                       \
		vec = vec op md_math::vec3_s({1, 1, 1});                               \
		md_math::vec3_s expected2({x op 1, y op 1, z op 1});                   \
		EXPECT_NEAR(vec.x(), expected2.x(), 1e-5);                             \
		EXPECT_NEAR(vec.y(), expected2.y(), 1e-5);                             \
		EXPECT_NEAR(vec.z(), expected2.z(), 1e-5);                             \
	}

#define VEC_OP_TEST_4D(op, test_name)                                          \
	TEST_SIGNATURE_4D(test_name) {                                             \
		srand(time(0));                                                        \
		float x = (float) (rand() % 100), y = (float) (rand() % 100),          \
			  z = (float) (rand() % 100), w = (float) (rand() % 100);          \
		md_math::vec4_s vec({x, y, z, w});                                     \
		vec = vec op vec;                                                      \
		md_math::vec4_s expected1({x op x, y op y, z op z, w op w});           \
		EXPECT_NEAR(vec.x(), expected1.x(), 1e-5);                             \
		EXPECT_NEAR(vec.y(), expected1.y(), 1e-5);                             \
		EXPECT_NEAR(vec.z(), expected1.z(), 1e-5);                             \
		EXPECT_NEAR(vec.w(), expected1.w(), 1e-5);                             \
		vec = {x, y, z, w};                                                    \
		vec = vec op md_math::vec4_s({1, 1, 1, 1});                            \
		md_math::vec4_s expected2({x op 1, y op 1, z op 1, w op 1});           \
		EXPECT_NEAR(vec.x(), expected2.x(), 1e-5);                             \
		EXPECT_NEAR(vec.y(), expected2.y(), 1e-5);                             \
		EXPECT_NEAR(vec.z(), expected2.z(), 1e-5);                             \
		EXPECT_NEAR(vec.w(), expected2.w(), 1e-5);                             \
	}


VEC_OP_TEST_2D(+, add_test)
VEC_OP_TEST_2D(-, sub_test)
VEC_OP_TEST_2D(*, mul_test)
VEC_OP_TEST_2D(/, div_test)

VEC_OP_TEST_3D(+, add_test)
VEC_OP_TEST_3D(-, sub_test)
VEC_OP_TEST_3D(*, mul_test)
VEC_OP_TEST_3D(/, div_test)

VEC_OP_TEST_4D(+, add_test)
VEC_OP_TEST_4D(-, sub_test)
VEC_OP_TEST_4D(*, mul_test)
VEC_OP_TEST_4D(/, div_test)

TEST_SIGNATURE_2D(magnitude_test) {
	srand(time(0));
	float x = (float) (rand() % 5) + 1, y = (float) (rand() % 5) + 1;
	md_math::vec2_s vec({x, y});
	EXPECT_NEAR(vec.magnitude(), std::sqrt(x * x + y * y), 1e-5);
	vec = vec.normalize();
	EXPECT_NEAR(vec.magnitude(), 1.0f, 1e-5);
}

TEST_SIGNATURE_3D(magnitude_test) {
	srand(time(0));
	float x = (float) (rand() % 5) + 1, y = (float) (rand() % 5) + 1,
		  z = (float) (rand() % 5) + 1;
	md_math::vec3_s vec({x, y, z});
	EXPECT_NEAR(vec.magnitude(), std::sqrt(x * x + y * y + z * z), 1e-5);
	vec = vec.normalize();
	EXPECT_NEAR(vec.magnitude(), 1.0f, 1e-5);
}

TEST_SIGNATURE_4D(magnitude_test) {
	srand(time(0));
	float x = (float) (rand() % 5) + 1, y = (float) (rand() % 5) + 1,
		  z = (float) (rand() % 5) + 1, w = (float) (rand() % 5) + 1;
	md_math::vec4_s vec({x, y, z, w});
	EXPECT_NEAR(vec.magnitude(), std::sqrt(x * x + y * y + z * z + w * w),
				1e-5);
	vec = vec.normalize();
	EXPECT_NEAR(vec.magnitude(), 1.0f, 1e-5);
}

TEST_SIGNATURE_2D(dot_test) {
	srand(time(0));
	float x = (float) (rand() % 5), y = (float) (rand() % 5);
	md_math::vec2_s vec1({x, y});
	md_math::vec2_s vec2({x, y});
	EXPECT_EQ(vec1.dot(vec2), x * x + y * y);
}

TEST_SIGNATURE_3D(dot_test) {
	srand(time(0));
	float x = (float) (rand() % 5), y = (float) (rand() % 5),
		  z = (float) (rand() % 5);
	md_math::vec3_s vec1({x, y, z});
	md_math::vec3_s vec2({x, y, z});
	EXPECT_EQ(vec1.dot(vec2), x * x + y * y + z * z);
}

TEST_SIGNATURE_4D(dot_test) {
	srand(time(0));
	float x = (float) (rand() % 5), y = (float) (rand() % 5),
		  z = (float) (rand() % 5), w = (float) (rand() % 5);
	md_math::vec4_s vec1({x, y, z, w});
	md_math::vec4_s vec2({x, y, z, w});
	EXPECT_EQ(vec1.dot(vec2), x * x + y * y + z * z + w * w);
}

TEST_SIGNATURE_2D(angle_test) {
	md_math::dvec2_s vec1({1, 0});
	md_math::dvec2_s vec2({0, 1});
	EXPECT_NEAR(vec1.angle(vec2), M_PI_2, 1e-5);
}

TEST_SIGNATURE_3D(angle_test) {
	md_math::dvec3_s vec1({1, 0, 0});
	md_math::dvec3_s vec2({0, 1, 0});
	EXPECT_NEAR(vec1.angle(vec2), M_PI_2, 1e-5);
}

TEST_SIGNATURE_4D(angle_test) {
	md_math::dvec4_s vec1({1, 0, 0, 0});
	md_math::dvec4_s vec2({0, 1, 0, 0});
	EXPECT_NEAR(vec1.angle(vec2), M_PI_2, 1e-5);
}