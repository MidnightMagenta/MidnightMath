#ifndef MATRIX_H
#define MATRIX_H

#include "../include/vector.hpp"
#include <cassert>

namespace md_math {
template<typename t_scalar, size_t t_size, bool t_simd>
struct matrix { /*void*/
};

#define NON_SIMD_MATRIX_TEMPLATE template<typename t_scalar, size_t t_size>
#define NON_SIMD_MATRIX matrix<t_scalar, t_size, false>
#define NON_SIMD_VECTOR vec<t_scalar, t_size, false>

NON_SIMD_MATRIX_TEMPLATE
NON_SIMD_MATRIX &GenericSetIdentity(NON_SIMD_MATRIX *src) {
	for (size_t i = 0; i < t_size; i++) {
		for (size_t j = 0; j < t_size; j++) {
			src->columns[i].data[j] = t_scalar((i == j) ? 1 : 0);
		}
	}

	return *src;
}

NON_SIMD_MATRIX_TEMPLATE
NON_SIMD_MATRIX &GenericSetTranspose(const NON_SIMD_MATRIX &src,
									 NON_SIMD_MATRIX *target) {
	for (size_t i = 0; i < t_size; ++i) {
		for (size_t j = i; j < t_size; ++j) {
			const t_scalar temp = src.columns[i].data[j];
			target->columns[i].data[j] = src.columns[j].data[i];
			target->columns[j].data[i] = temp;
		}
	}

	return *target;
}

NON_SIMD_MATRIX_TEMPLATE
NON_SIMD_MATRIX &GenericMatrixMultiply(const NON_SIMD_MATRIX &a,
									   const NON_SIMD_MATRIX &b,
									   NON_SIMD_MATRIX *target) {
	for (size_t col = 0; col < t_size; ++col) {
		for (size_t row = 0; row < t_size; ++row) {
			t_scalar dot = 0;
			for (size_t i = 0; i < t_size; ++i) {
				dot += a.columns[i].data[row] * b.columns[col].data[i];
			}

			target->columns[col].data[row] = dot;
		}
	}

	return *target;
}

NON_SIMD_MATRIX_TEMPLATE
NON_SIMD_VECTOR GenericVectorMultiply(const NON_SIMD_MATRIX &mat,
										const NON_SIMD_VECTOR &v) {
	NON_SIMD_VECTOR result = mat.columns[0] * v.data[0];
	for (unsigned int i = 1; i < t_size; ++i) {
		result += mat.columns[i] * v.data[i];
	}

	return result;
}

template<typename t_scalar_, size_t t_size>
struct matrix<t_scalar_, t_size, false> {
	typedef t_scalar_ t_scalar;
	typedef vec<t_scalar_, t_size, false> t_vec;
	typedef matrix<t_scalar_, t_size, false> t_matrix;

	t_vec columns[t_size];

	inline t_matrix &SetIdentity() { return GenericSetIdentity(this); }
	inline t_matrix &SetTranspose(t_matrix *target) const {
		return GenericSetTranspose(*this, target);
	}
	inline t_matrix &SetTranspose() { return SetTranspose(this); }

	inline t_vec operator*(const t_vec &v) const {
		return GenericVectorMultiply(*this, v);
	}

	inline t_matrix &multiply(const t_matrix &mat, t_matrix *target) const {
		assert(&mat != target);
		assert(this != target);
		return GenericMatrixMultiply(*this, mat, target);
	}

	inline t_matrix operator*(const t_matrix &mat) const {
		t_matrix result;
		return multiply(mat, &result);
	}

	inline t_matrix operator*=(const t_matrix &m) {
		return *this = (*this) * m;
	}
};

template<typename t_scalar_>
struct matrix<t_scalar_, 4, true> {
	typedef t_scalar_ t_scalar;
	typedef vec<t_scalar, 4, true> t_vec;
	typedef matrix<t_scalar, 4, true> t_matrix;

	t_vec columns[4];

	inline matrix() {}
	inline matrix(const t_vec &c0, const t_vec &c1, const t_vec &c2,
				  const t_vec &c3) {
		set(c0, c1, c2, c3);
	}

	inline void set(const t_vec &c0, const t_vec &c1, const t_vec &c2,
					const t_vec &c3) {
		columns[0] = c0;
		columns[1] = c1;
		columns[2] = c2;
		columns[3] = c3;
	}

	inline t_matrix &set_identity() {
		columns[0] = vec4{1.0f, 0.0f, 0.0f, 0.0f};
		columns[1] = vec4{0.0f, 1.0f, 0.0f, 0.0f};
		columns[2] = vec4{0.0f, 0.0f, 1.0f, 0.0f};
		columns[3] = vec4{0.0f, 0.0f, 0.0f, 1.0f};

		return *this;
	}

	inline t_matrix &set_transpose(t_matrix *target) const {
		const __m128 t0 =
				_mm_shuffle_ps(columns[0].data_v, columns[1].data_v, 0x44);
		const __m128 t1 =
				_mm_shuffle_ps(columns[0].data_v, columns[1].data_v, 0xEE);
		const __m128 t2 =
				_mm_shuffle_ps(columns[2].data_v, columns[3].data_v, 0x44);
		const __m128 t3 =
				_mm_shuffle_ps(columns[2].data_v, columns[3].data_v, 0xEE);

		target->columns[0] = _mm_shuffle_ps(t0, t2, 0x88);
		target->columns[1] = _mm_shuffle_ps(t0, t2, 0xDD);
		target->columns[2] = _mm_shuffle_ps(t1, t3, 0x88);
		target->columns[3] = _mm_shuffle_ps(t1, t3, 0xDD);

		return *target;
	}


	inline t_matrix &set_transpose() { return set_transpose(this); }
	inline t_matrix transpose() {
		t_matrix result;
		return set_transpose(&result);
	}

	inline t_vec operator*(const t_vec &v) const {
		t_vec v_x = _mm_shuffle_ps(
				v.data_v, v.data_v, MD_SHUFFLE(MD_S_X, MD_S_X, MD_S_X, MD_S_X));
		t_vec v_y = _mm_shuffle_ps(
				v.data_v, v.data_v, MD_SHUFFLE(MD_S_Y, MD_S_Y, MD_S_Y, MD_S_Y));
		t_vec v_z = _mm_shuffle_ps(
				v.data_v, v.data_v, MD_SHUFFLE(MD_S_Z, MD_S_Z, MD_S_Z, MD_S_Z));
		t_vec v_w = _mm_shuffle_ps(
				v.data_v, v.data_v, MD_SHUFFLE(MD_S_W, MD_S_W, MD_S_W, MD_S_W));

		return v_x * columns[0] + v_y * columns[1] + v_z * columns[2] +
			   v_w * columns[3];
	}

	inline t_matrix &multiply(const t_matrix &m, t_matrix *target) const {
		assert(&m != target);
		assert(this != target);

		target->columns[0] = (*this) * m.columns[0];
		target->columns[1] = (*this) * m.columns[1];
		target->columns[2] = (*this) * m.columns[2];
		target->columns[3] = (*this) * m.columns[3];

		return *target;
	}

	inline t_matrix operator*(const t_matrix &v) const {
		t_matrix result;
		return multiply(v, &result);
	}

	inline t_matrix operator*=(const t_matrix &v) {
		return *this = (*this) * v;
	}
};

typedef matrix<float, 3, false> mat33_s;
typedef matrix<float, 4, false> mat44_s, mat_s;
typedef matrix<double, 3, false> dmat33_s;
typedef matrix<double, 4, false> dmat44_s, dmat_s;

typedef matrix<float, 4, true> mat44_v;

typedef mat33_s mat3;
typedef mat44_s mat4;
}// namespace md_math
#endif// !MATRIX_H