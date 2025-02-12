#include "../include/matrix.hpp"
#include <gtest/gtest.h>

using namespace md_math;

const float TOLERANCE = 1e-5;

TEST(NonSimdMatrix, SetIdentity) {
	mat3 matrix;
	matrix.SetIdentity();

	for (size_t i = 0; i < 3; ++i) {
		for (size_t j = 0; j < 3; ++j) {
			if (i == j) {
				EXPECT_NEAR(matrix.columns[i].data[j], 1.0f, TOLERANCE);
			} else {
				EXPECT_NEAR(matrix.columns[i].data[j], 0.0f, TOLERANCE);
			}
		}
	}
}

TEST(NonSimdMatrix, SetTranspose) {
	mat3 matrix;
	matrix.columns[0] = {1.0f, 2.0f, 3.0f};
	matrix.columns[1] = {4.0f, 5.0f, 6.0f};
	matrix.columns[2] = {7.0f, 8.0f, 9.0f};

	mat3 transposed;
	matrix.SetTranspose(&transposed);

	EXPECT_NEAR(transposed.columns[0].data[0], 1.0f, TOLERANCE);
	EXPECT_NEAR(transposed.columns[0].data[1], 4.0f, TOLERANCE);
	EXPECT_NEAR(transposed.columns[0].data[2], 7.0f, TOLERANCE);
	EXPECT_NEAR(transposed.columns[1].data[0], 2.0f, TOLERANCE);
	EXPECT_NEAR(transposed.columns[1].data[1], 5.0f, TOLERANCE);
	EXPECT_NEAR(transposed.columns[1].data[2], 8.0f, TOLERANCE);
	EXPECT_NEAR(transposed.columns[2].data[0], 3.0f, TOLERANCE);
	EXPECT_NEAR(transposed.columns[2].data[1], 6.0f, TOLERANCE);
	EXPECT_NEAR(transposed.columns[2].data[2], 9.0f, TOLERANCE);
}

TEST(NonSimdMatrix, MatrixMultiply) {
	mat3 matrixA;
	matrixA.columns[0] = {1.0f, 2.0f, 3.0f};
	matrixA.columns[1] = {4.0f, 5.0f, 6.0f};
	matrixA.columns[2] = {7.0f, 8.0f, 9.0f};

	mat3 matrixB;
	matrixB.columns[0] = {9.0f, 8.0f, 7.0f};
	matrixB.columns[1] = {6.0f, 5.0f, 4.0f};
	matrixB.columns[2] = {3.0f, 2.0f, 1.0f};

	mat3 result;
	matrixA.multiply(matrixB, &result);

	EXPECT_NEAR(result.columns[0].data[0], 90.0f, TOLERANCE);
	EXPECT_NEAR(result.columns[0].data[1], 114.0f, TOLERANCE);
	EXPECT_NEAR(result.columns[0].data[2], 138.0f, TOLERANCE);
	EXPECT_NEAR(result.columns[1].data[0], 54.0f, TOLERANCE);
	EXPECT_NEAR(result.columns[1].data[1], 69.0f, TOLERANCE);
	EXPECT_NEAR(result.columns[1].data[2], 84.0f, TOLERANCE);
	EXPECT_NEAR(result.columns[2].data[0], 18.0f, TOLERANCE);
	EXPECT_NEAR(result.columns[2].data[1], 24.0f, TOLERANCE);
	EXPECT_NEAR(result.columns[2].data[2], 30.0f, TOLERANCE);
}

TEST(SimdMatrix, SetIdentity) {
	mat44_v matrix;
	matrix.set_identity();

	EXPECT_NEAR(matrix.columns[0].data[0], 1.0f, TOLERANCE);
	EXPECT_NEAR(matrix.columns[0].data[1], 0.0f, TOLERANCE);
	EXPECT_NEAR(matrix.columns[0].data[2], 0.0f, TOLERANCE);
	EXPECT_NEAR(matrix.columns[0].data[3], 0.0f, TOLERANCE);
	EXPECT_NEAR(matrix.columns[1].data[0], 0.0f, TOLERANCE);
	EXPECT_NEAR(matrix.columns[1].data[1], 1.0f, TOLERANCE);
	EXPECT_NEAR(matrix.columns[1].data[2], 0.0f, TOLERANCE);
	EXPECT_NEAR(matrix.columns[1].data[3], 0.0f, TOLERANCE);
	EXPECT_NEAR(matrix.columns[2].data[0], 0.0f, TOLERANCE);
	EXPECT_NEAR(matrix.columns[2].data[1], 0.0f, TOLERANCE);
	EXPECT_NEAR(matrix.columns[2].data[2], 1.0f, TOLERANCE);
	EXPECT_NEAR(matrix.columns[2].data[3], 0.0f, TOLERANCE);
	EXPECT_NEAR(matrix.columns[3].data[0], 0.0f, TOLERANCE);
	EXPECT_NEAR(matrix.columns[3].data[1], 0.0f, TOLERANCE);
	EXPECT_NEAR(matrix.columns[3].data[2], 0.0f, TOLERANCE);
	EXPECT_NEAR(matrix.columns[3].data[3], 1.0f, TOLERANCE);
}

TEST(SimdMatrix, SetTranspose) {
	mat44_v matrix;
	matrix.columns[0] = vec4{1.0f, 2.0f, 3.0f, 4.0f};
	matrix.columns[1] = vec4{5.0f, 6.0f, 7.0f, 8.0f};
	matrix.columns[2] = vec4{9.0f, 10.0f, 11.0f, 12.0f};
	matrix.columns[3] = vec4{13.0f, 14.0f, 15.0f, 16.0f};

	mat44_v transposed;
	matrix.set_transpose(&transposed);

	EXPECT_NEAR(transposed.columns[0].data[0], 1.0f, TOLERANCE);
	EXPECT_NEAR(transposed.columns[0].data[1], 5.0f, TOLERANCE);
	EXPECT_NEAR(transposed.columns[0].data[2], 9.0f, TOLERANCE);
	EXPECT_NEAR(transposed.columns[0].data[3], 13.0f, TOLERANCE);
	EXPECT_NEAR(transposed.columns[1].data[0], 2.0f, TOLERANCE);
	EXPECT_NEAR(transposed.columns[1].data[1], 6.0f, TOLERANCE);
	EXPECT_NEAR(transposed.columns[1].data[2], 10.0f, TOLERANCE);
	EXPECT_NEAR(transposed.columns[1].data[3], 14.0f, TOLERANCE);
	EXPECT_NEAR(transposed.columns[2].data[0], 3.0f, TOLERANCE);
	EXPECT_NEAR(transposed.columns[2].data[1], 7.0f, TOLERANCE);
	EXPECT_NEAR(transposed.columns[2].data[2], 11.0f, TOLERANCE);
	EXPECT_NEAR(transposed.columns[2].data[3], 15.0f, TOLERANCE);
	EXPECT_NEAR(transposed.columns[3].data[0], 4.0f, TOLERANCE);
	EXPECT_NEAR(transposed.columns[3].data[1], 8.0f, TOLERANCE);
	EXPECT_NEAR(transposed.columns[3].data[2], 12.0f, TOLERANCE);
	EXPECT_NEAR(transposed.columns[3].data[3], 16.0f, TOLERANCE);
}

TEST(SimdMatrix, MatrixMultiply) {
	mat44_v matrixA;
	matrixA.columns[0] = vec4{1.0f, 2.0f, 3.0f, 4.0f};
	matrixA.columns[1] = vec4{5.0f, 6.0f, 7.0f, 8.0f};
	matrixA.columns[2] = vec4{9.0f, 10.0f, 11.0f, 12.0f};
	matrixA.columns[3] = vec4{13.0f, 14.0f, 15.0f, 16.0f};

	mat44_v matrixB;
	matrixB.columns[0] = vec4{16.0f, 15.0f, 14.0f, 13.0f};
	matrixB.columns[1] = vec4{12.0f, 11.0f, 10.0f, 9.0f};
	matrixB.columns[2] = vec4{8.0f, 7.0f, 6.0f, 5.0f};
	matrixB.columns[3] = vec4{4.0f, 3.0f, 2.0f, 1.0f};

	mat44_v result;
	matrixA.mul(matrixB, &result);

	EXPECT_NEAR(result.columns[0].data[0], 386.0f, TOLERANCE);
	EXPECT_NEAR(result.columns[0].data[1], 444.0f, TOLERANCE);
	EXPECT_NEAR(result.columns[0].data[2], 502.0f, TOLERANCE);
	EXPECT_NEAR(result.columns[0].data[3], 560.0f, TOLERANCE);
	EXPECT_NEAR(result.columns[1].data[0], 274.0f, TOLERANCE);
	EXPECT_NEAR(result.columns[1].data[1], 316.0f, TOLERANCE);
	EXPECT_NEAR(result.columns[1].data[2], 358.0f, TOLERANCE);
	EXPECT_NEAR(result.columns[1].data[3], 400.0f, TOLERANCE);
	EXPECT_NEAR(result.columns[2].data[0], 162.0f, TOLERANCE);
	EXPECT_NEAR(result.columns[2].data[1], 188.0f, TOLERANCE);
	EXPECT_NEAR(result.columns[2].data[2], 214.0f, TOLERANCE);
	EXPECT_NEAR(result.columns[2].data[3], 240.0f, TOLERANCE);
	EXPECT_NEAR(result.columns[3].data[0], 50.0f, TOLERANCE);
	EXPECT_NEAR(result.columns[3].data[1], 60.0f, TOLERANCE);
	EXPECT_NEAR(result.columns[3].data[2], 70.0f, TOLERANCE);
	EXPECT_NEAR(result.columns[3].data[3], 80.0f, TOLERANCE);
}
