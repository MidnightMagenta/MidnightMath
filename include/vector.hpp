#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <initializer_list>
#include <inttypes.h>

#define FORCEINLINE __forceinline

namespace md_math {
template<typename t_scalar, size_t t_size, bool t_enable_simd>
struct vec {};

#define MD_MATH_ALIAS(name, index)                                             \
	constexpr t_scalar &name() { return data[index]; }

#define MD_MATH_DEFINE_VEC typedef vec<t_scalar_, t_size, t_simd> t_vec
#define MD_MATH_DEFINE_SCALAR typedef t_scalar_ t_scalar

#define MD_MATH_VEC_DEFINES(size, simd)                                        \
	static constexpr size_t t_size = size;                                     \
	static constexpr bool t_simd = simd;                                       \
	MD_MATH_DEFINE_VEC;                                                        \
	MD_MATH_DEFINE_SCALAR;

#define MD_INITIALIZER_LIST_CONSTRUCTOR                                        \
	vec(std::initializer_list<int> list) {                                     \
		if (list.size() == t_size) {                                           \
			auto initializer = list.begin();                                   \
			for (size_t i = 0; i < t_size; i++) {                              \
				data[i] = (int) initializer[i];                                \
			}                                                                  \
		}                                                                      \
	}                                                                          \
	vec(std::initializer_list<float> list) {                                   \
		if (list.size() == t_size) {                                           \
			auto initializer = list.begin();                                   \
			for (size_t i = 0; i < t_size; i++) {                              \
				data[i] = (float) initializer[i];                              \
			}                                                                  \
		}                                                                      \
	}                                                                          \
	vec(std::initializer_list<double> list) {                                  \
		if (list.size() == t_size) {                                           \
			auto initializer = list.begin();                                   \
			for (size_t i = 0; i < t_size; i++) {                              \
				data[i] = (double) initializer[i];                             \
			}                                                                  \
		}                                                                      \
	}                                                                          \
	vec(std::initializer_list<unsigned int> list) {                            \
		if (list.size() == t_size) {                                           \
			auto initializer = list.begin();                                   \
			for (size_t i = 0; i < t_size; i++) {                              \
				data[i] = (unsigned int) initializer[i];                       \
			}                                                                  \
		}                                                                      \
	}

#define MD_MATH_VEC_CONSTRUCTORS                                               \
	vec(int s) {                                                               \
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) s; }        \
	}                                                                          \
	vec(float s) {                                                             \
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) s; }        \
	}                                                                          \
	vec(double s) {                                                            \
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) s; }        \
	}                                                                          \
	vec(unsigned int s) {                                                      \
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) s; }        \
	}

#define MD_MATH_DEFAULT_CONSTRUCTOR                                            \
	vec() {                                                                    \
		for (size_t i = 0; i < t_size; i++) { data[i] = t_scalar(); }          \
	}

#define MD_MATH_DEFAULT_DESTRUCTOR                                             \
	~vec() {}

#define MD_MATH_DEFINE_COMPONENT_WISE_OP(op)                                   \
	FORCEINLINE t_vec operator op(const t_vec &b) {                            \
		t_vec result;                                                          \
		for (size_t i = 0; i < t_size; i++) {                                  \
			result.data[i] = data[i] op b.data[i];                             \
		}                                                                      \
		return result;                                                         \
	}

#define MD_MATH_DEFINE_SCALAR_OP(op)                                           \
	FORCEINLINE t_vec operator op(t_scalar b) {                                \
		t_vec result;                                                          \
		for (size_t i = 0; i < t_size; i++) { result.data[i] = data[i] op b; } \
		return result;                                                         \
	}

#define MD_MATH_DEFINE_BOOLEAN_OP(op)                                          \
	FORCEINLINE bool operator op(const t_vec &b) const {                       \
		for (size_t i = 0; i < t_size; i++) {                                  \
			if (!(data[i] op b.data[i])) { return false; }                     \
		}                                                                      \
		return true;                                                           \
	}

#define MD_MATH_ASSIGNMENT_OP(full_op, op)                                     \
	FORCEINLINE t_vec &operator full_op(const t_vec & b) {                     \
		for (size_t i = 0; i < t_size; i++) {                                  \
			data[i] = data[i] op b.data[i];                                    \
		}                                                                      \
		return *this;                                                          \
	}

#define MD_MATH_ASSIGNMENT                                                     \
	FORCEINLINE t_vec &operator=(std::initializer_list<t_scalar> list) {       \
		if (list.size() == t_size) {                                           \
			auto initializer = list.begin();                                   \
			for (size_t i = 0; i < t_size; i++) { data[i] = initializer[i]; }  \
		}                                                                      \
		return *this;                                                          \
	}                                                                          \
	template<typename t_b_type>                                                \
	FORCEINLINE t_vec operator=(const t_b_type &b) {                           \
		size_t l = (t_size < t_b_type::t_size) ? t_size : t_b_type::t_size;    \
		for (size_t i = 0; i < t_size; i++) { data[i] = t_scalar(b.data[i]); } \
		for (size_t i = l; i < t_size; i++) { data[i] = t_scalar(0); }         \
		return *this;                                                          \
	}

#define MD_MATH_NEGATE_OP                                                      \
	FORCEINLINE t_vec operator-() const {                                      \
		t_vec result;                                                          \
		for (size_t i = 0; i < t_size; i++) { result.data[i] = -data[i]; }     \
		return result;                                                         \
	}

#define MD_MATH_DEFINE_LENGTH                                                  \
	FORCEINLINE t_scalar length() const {                                      \
		t_scalar sum = 0;                                                      \
		for (size_t i = 0; i < t_size; i++) {                                  \
			sum += data[i] * data[i];                                          \
		}                                                                      \
		return std::sqrt(sum);                                                 \
	}

#define MD_MATH_DEFINE_NORMALIZE                                               \
	FORCEINLINE void normalize() {                                             \
		t_scalar _length = length();                                           \
		for (size_t i = 0; i < t_size; i++) { data[i] /= _length; }            \
	}
#define MD_MATH_DEFINE_DOT                                                     \
	FORCEINLINE t_scalar dot(const t_vec &b) {                                 \
		t_scalar result = 0;                                                   \
		for (size_t i = 0; i < t_size; i++) { result += data[i] * b.data[i]; } \
		return result;                                                         \
	}

#define MD_MATH_DEFINE_ANGLE                                                   \
	FORCEINLINE t_scalar angle(const t_vec &b) {                               \
		return std::acos(dot(b) / (length() * b.length()));                    \
	}

//non SIMD vectors
template<typename t_scalar_>
struct vec<t_scalar_, 1, false> {
	MD_MATH_VEC_DEFINES(1, false)
	t_scalar data[t_size];

	MD_MATH_ALIAS(s, 0)

	MD_INITIALIZER_LIST_CONSTRUCTOR
	MD_MATH_VEC_CONSTRUCTORS
	MD_MATH_DEFAULT_CONSTRUCTOR
	MD_MATH_DEFAULT_DESTRUCTOR

	MD_MATH_ASSIGNMENT

	MD_MATH_DEFINE_COMPONENT_WISE_OP(+)
	MD_MATH_DEFINE_COMPONENT_WISE_OP(-)
	MD_MATH_DEFINE_COMPONENT_WISE_OP(/)
	MD_MATH_DEFINE_COMPONENT_WISE_OP(*)
	MD_MATH_DEFINE_SCALAR_OP(+)
	MD_MATH_DEFINE_SCALAR_OP(-)
	MD_MATH_DEFINE_SCALAR_OP(*)
	MD_MATH_DEFINE_SCALAR_OP(/)
	MD_MATH_NEGATE_OP

	MD_MATH_DEFINE_BOOLEAN_OP(==)
	MD_MATH_DEFINE_BOOLEAN_OP(<=)
	MD_MATH_DEFINE_BOOLEAN_OP(>=)
	MD_MATH_DEFINE_BOOLEAN_OP(<)
	MD_MATH_DEFINE_BOOLEAN_OP(>)
	MD_MATH_DEFINE_BOOLEAN_OP(!=)

	MD_MATH_ASSIGNMENT_OP(+=, +)
	MD_MATH_ASSIGNMENT_OP(-=, -)
	MD_MATH_ASSIGNMENT_OP(*=, *)
	MD_MATH_ASSIGNMENT_OP(/=, /)

	MD_MATH_DEFINE_LENGTH
	MD_MATH_DEFINE_NORMALIZE
	MD_MATH_DEFINE_DOT
	MD_MATH_DEFINE_ANGLE
};
template<typename t_scalar_>
struct vec<t_scalar_, 2, false> {
	MD_MATH_VEC_DEFINES(2, false)
	t_scalar data[t_size];

	MD_MATH_ALIAS(x, 0)
	MD_MATH_ALIAS(y, 1)

	MD_MATH_ALIAS(w, 0)
	MD_MATH_ALIAS(h, 1)

	MD_MATH_ALIAS(s, 0)
	MD_MATH_ALIAS(t, 1)

	MD_MATH_ALIAS(r, 0)
	MD_MATH_ALIAS(g, 1)

	MD_INITIALIZER_LIST_CONSTRUCTOR
	MD_MATH_VEC_CONSTRUCTORS
	MD_MATH_DEFAULT_CONSTRUCTOR
	MD_MATH_DEFAULT_DESTRUCTOR

	vec(t_scalar x, t_scalar y) {
		data[0] = x;
		data[1] = y;
	}

	MD_MATH_ASSIGNMENT

	MD_MATH_DEFINE_COMPONENT_WISE_OP(+)
	MD_MATH_DEFINE_COMPONENT_WISE_OP(-)
	MD_MATH_DEFINE_COMPONENT_WISE_OP(/)
	MD_MATH_DEFINE_COMPONENT_WISE_OP(*)
	MD_MATH_DEFINE_SCALAR_OP(+)
	MD_MATH_DEFINE_SCALAR_OP(-)
	MD_MATH_DEFINE_SCALAR_OP(*)
	MD_MATH_DEFINE_SCALAR_OP(/)
	MD_MATH_NEGATE_OP

	MD_MATH_DEFINE_BOOLEAN_OP(==)
	MD_MATH_DEFINE_BOOLEAN_OP(<=)
	MD_MATH_DEFINE_BOOLEAN_OP(>=)
	MD_MATH_DEFINE_BOOLEAN_OP(<)
	MD_MATH_DEFINE_BOOLEAN_OP(>)
	MD_MATH_DEFINE_BOOLEAN_OP(!=)

	MD_MATH_ASSIGNMENT_OP(+=, +)
	MD_MATH_ASSIGNMENT_OP(-=, -)
	MD_MATH_ASSIGNMENT_OP(*=, *)
	MD_MATH_ASSIGNMENT_OP(/=, /)

	MD_MATH_DEFINE_LENGTH
	MD_MATH_DEFINE_NORMALIZE
	MD_MATH_DEFINE_DOT
	MD_MATH_DEFINE_ANGLE
};
template<typename t_scalar_>
struct vec<t_scalar_, 3, false> {
	MD_MATH_VEC_DEFINES(3, false)
	t_scalar data[t_size];

	MD_MATH_ALIAS(x, 0)
	MD_MATH_ALIAS(y, 1)
	MD_MATH_ALIAS(z, 2)

	MD_MATH_ALIAS(r, 0)
	MD_MATH_ALIAS(g, 1)
	MD_MATH_ALIAS(b, 2)

	MD_INITIALIZER_LIST_CONSTRUCTOR
	MD_MATH_VEC_CONSTRUCTORS
	MD_MATH_DEFAULT_CONSTRUCTOR
	MD_MATH_DEFAULT_DESTRUCTOR

	vec(t_scalar x, t_scalar y, t_scalar z) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
	}

	MD_MATH_ASSIGNMENT

	MD_MATH_DEFINE_COMPONENT_WISE_OP(+)
	MD_MATH_DEFINE_COMPONENT_WISE_OP(-)
	MD_MATH_DEFINE_COMPONENT_WISE_OP(/)
	MD_MATH_DEFINE_COMPONENT_WISE_OP(*)
	MD_MATH_DEFINE_SCALAR_OP(+)
	MD_MATH_DEFINE_SCALAR_OP(-)
	MD_MATH_DEFINE_SCALAR_OP(*)
	MD_MATH_DEFINE_SCALAR_OP(/)
	MD_MATH_NEGATE_OP

	MD_MATH_DEFINE_BOOLEAN_OP(==)
	MD_MATH_DEFINE_BOOLEAN_OP(<=)
	MD_MATH_DEFINE_BOOLEAN_OP(>=)
	MD_MATH_DEFINE_BOOLEAN_OP(<)
	MD_MATH_DEFINE_BOOLEAN_OP(>)
	MD_MATH_DEFINE_BOOLEAN_OP(!=)

	MD_MATH_ASSIGNMENT_OP(+=, +)
	MD_MATH_ASSIGNMENT_OP(-=, -)
	MD_MATH_ASSIGNMENT_OP(*=, *)
	MD_MATH_ASSIGNMENT_OP(/=, /)

	MD_MATH_DEFINE_LENGTH
	MD_MATH_DEFINE_NORMALIZE
	MD_MATH_DEFINE_DOT
	MD_MATH_DEFINE_ANGLE

	t_vec cross(const t_vec &b) const {
		return {y() * b.z() - z() * b.y(), z() * b.x() - x() * b.z(),
				x() * b.y() - y() * b.x()};
	}
};
template<typename t_scalar_>
struct vec<t_scalar_, 4, false> {
	MD_MATH_VEC_DEFINES(4, false)
	t_scalar data[t_size];

	MD_MATH_ALIAS(x, 0)
	MD_MATH_ALIAS(y, 1)
	MD_MATH_ALIAS(z, 2)
	MD_MATH_ALIAS(w, 3)

	MD_MATH_ALIAS(r, 0)
	MD_MATH_ALIAS(g, 1)
	MD_MATH_ALIAS(b, 2)
	MD_MATH_ALIAS(a, 3)

	MD_INITIALIZER_LIST_CONSTRUCTOR
	MD_MATH_VEC_CONSTRUCTORS
	MD_MATH_DEFAULT_CONSTRUCTOR
	MD_MATH_DEFAULT_DESTRUCTOR

	vec(t_scalar x, t_scalar y, t_scalar z, t_scalar w) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
		data[3] = w;
	}

	MD_MATH_ASSIGNMENT

	MD_MATH_DEFINE_COMPONENT_WISE_OP(+)
	MD_MATH_DEFINE_COMPONENT_WISE_OP(-)
	MD_MATH_DEFINE_COMPONENT_WISE_OP(/)
	MD_MATH_DEFINE_COMPONENT_WISE_OP(*)
	MD_MATH_DEFINE_SCALAR_OP(+)
	MD_MATH_DEFINE_SCALAR_OP(-)
	MD_MATH_DEFINE_SCALAR_OP(*)
	MD_MATH_DEFINE_SCALAR_OP(/)
	MD_MATH_NEGATE_OP

	MD_MATH_DEFINE_BOOLEAN_OP(==)
	MD_MATH_DEFINE_BOOLEAN_OP(<=)
	MD_MATH_DEFINE_BOOLEAN_OP(>=)
	MD_MATH_DEFINE_BOOLEAN_OP(<)
	MD_MATH_DEFINE_BOOLEAN_OP(>)
	MD_MATH_DEFINE_BOOLEAN_OP(!=)

	MD_MATH_ASSIGNMENT_OP(+=, +)
	MD_MATH_ASSIGNMENT_OP(-=, -)
	MD_MATH_ASSIGNMENT_OP(*=, *)
	MD_MATH_ASSIGNMENT_OP(/=, /)

	MD_MATH_DEFINE_LENGTH
	MD_MATH_DEFINE_NORMALIZE
	MD_MATH_DEFINE_DOT
	MD_MATH_DEFINE_ANGLE
};

//generic non SIMD vector template
template<typename t_scalar_, size_t t_size_>
struct vec<t_scalar_, t_size_, false> {};

//SIMD vectors
template<>
struct vec<float, 4, true> {};
template<>
struct vec<float, 8, true> {};
template<>
struct vec<double, 2, true> {};
template<>
struct vec<double, 4, true> {};

typedef vec<unsigned int, 1, false> uvec1_s;
typedef vec<unsigned int, 2, false> uvec2_s;
typedef vec<unsigned int, 3, false> uvec3_s;
typedef vec<unsigned int, 4, false> uvec4_s;

typedef vec<int, 1, false> ivec1_s;
typedef vec<int, 2, false> ivec2_s;
typedef vec<int, 3, false> ivec3_s;
typedef vec<int, 4, false> ivec4_s;

typedef vec<float, 1, false> vec1_s;
typedef vec<float, 2, false> vec2_s;
typedef vec<float, 3, false> vec3_s;
typedef vec<float, 4, false> vec4_s, quat_s;

typedef vec<double, 1, false> dvec1_s;
typedef vec<double, 2, false> dvec2_s;
typedef vec<double, 3, false> dvec3_s;
typedef vec<double, 4, false> dvec4_s, dquat_s;

typedef vec<float, 4, true> vec4_v, quat_v;
typedef vec<float, 8, true> vec8_v;
typedef vec<double, 2, true> dvec2_v;
typedef vec<double, 4, true> dvec4_v;

typedef vec<uint8_t, 1, false> r_8;
typedef vec<uint8_t, 2, false> rg_16;
typedef vec<uint8_t, 3, false> rgb_24;
typedef vec<uint8_t, 4, false> rgba_32;


#ifdef MD_MATH_USE_SIMD
using vec4 = vec4_v;
using dvec2 = vec2_v;
using dvec4 = vec4_v;
#else
using vec4 = vec4_s;
using dvec2 = dvec2_s;
using dvec4 = dvec4_s;
#endif// MD_MATH_USE_SIMD

using vec2 = vec2_s;
using vec3 = vec3_s;

using ivec2 = ivec2_s;
using ivec3 = ivec3_s;
using ivec4 = ivec4_s;

}// namespace md_math

#endif// !VECTOR_H