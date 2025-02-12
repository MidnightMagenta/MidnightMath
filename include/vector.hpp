#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <immintrin.h>
#include <initializer_list>
#include <inttypes.h>

namespace md_math {
template<typename t_scalar, size_t t_size, bool t_enable_simd>
struct vec { /*void*/
};

#define MD_MATH_ALIAS(name, index)                                             \
	constexpr t_scalar &name() { return data[index]; }                         \
	constexpr const t_scalar &name() const { return data[index]; }


#define MD_MATH_DEFINE_VEC typedef vec<t_scalar_, t_size, t_simd> t_vec
#define MD_MATH_DEFINE_SCALAR typedef t_scalar_ t_scalar

#define MD_MATH_VEC_DEFINES(size, simd)                                        \
	static constexpr size_t t_size = size;                                     \
	static constexpr bool t_simd = simd;                                       \
	MD_MATH_DEFINE_VEC;                                                        \
	MD_MATH_DEFINE_SCALAR;

#define MD_S_X 0
#define MD_S_Y 1
#define MD_S_Z 2
#define MD_S_W 3
#define MD_SHUFFLE(p0, p1, p2, p3) _MM_SHUFFLE((p3), (p2), (p1), (p0))

//non SIMD vectors

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

	vec(std::initializer_list<int> list) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) 0; }
		if (list.size() == t_size) {
			auto initializer = list.begin();
			data[0] = (t_scalar) initializer[0];
			data[1] = (t_scalar) initializer[1];
		}
	}
	vec(std::initializer_list<float> list) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) 0; }
		if (list.size() == t_size) {
			auto initializer = list.begin();
			data[0] = (t_scalar) initializer[0];
			data[1] = (t_scalar) initializer[1];
		}
	}
	vec(std::initializer_list<double> list) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) 0; }
		if (list.size() == t_size) {
			auto initializer = list.begin();
			data[0] = (t_scalar) initializer[0];
			data[1] = (t_scalar) initializer[1];
		}
	}
	vec(std::initializer_list<unsigned int> list) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) 0; }
		if (list.size() == t_size) {
			auto initializer = list.begin();
			data[0] = (t_scalar) initializer[0];
			data[1] = (t_scalar) initializer[1];
		}
	}
	vec(int s) {
		data[0] = (t_scalar) s;
		data[1] = (t_scalar) s;
	}
	vec(float s) {
		data[0] = (t_scalar) s;
		data[1] = (t_scalar) s;
	}
	vec(double s) {
		data[0] = (t_scalar) s;
		data[1] = (t_scalar) s;
	}
	vec(unsigned int s) {
		data[0] = (t_scalar) s;
		data[1] = (t_scalar) s;
	}
	vec() {
		data[0] = (t_scalar) 0;
		data[1] = (t_scalar) 0;
	}
	~vec() {}

	vec(t_scalar x, t_scalar y) {
		data[0] = x;
		data[1] = y;
	}

	inline t_vec &operator=(std::initializer_list<t_scalar> list) {
		if (list.size() == t_size) {
			auto initializer = list.begin();
			data[0] = (t_scalar) initializer[0];
			data[1] = (t_scalar) initializer[1];
		}
		return *this;
	}
	template<typename t_b_type>
	inline t_vec operator=(const t_b_type &b) {
		size_t l = (t_size < t_b_type::t_size) ? t_size : t_b_type::t_size;
		for (size_t i = 0; i < t_size; i++) { data[i] = t_scalar(b.data[i]); }
		for (size_t i = l; i < t_size; i++) { data[i] = t_scalar(0); }
		return *this;
	}

	inline t_vec operator+(const t_vec &b) {
		t_vec result;
		result.data[0] = data[0] + b.data[0];
		result.data[1] = data[1] + b.data[1];
		return result;
	}
	inline t_vec operator-(const t_vec &b) {
		t_vec result;
		result.data[0] = data[0] - b.data[0];
		result.data[1] = data[1] - b.data[1];
		return result;
	}
	inline t_vec operator/(const t_vec &b) {
		t_vec result;
		result.data[0] = data[0] / b.data[0];
		result.data[1] = data[1] / b.data[1];
		return result;
	}
	inline t_vec operator*(const t_vec &b) {
		t_vec result;
		result.data[0] = data[0] * b.data[0];
		result.data[1] = data[1] * b.data[1];
		return result;
	}
	inline t_vec operator+(t_scalar b) {
		t_vec result;
		result.data[0] = data[0] + b;
		result.data[1] = data[1] + b;
		return result;
	}
	inline t_vec operator-(t_scalar b) {
		t_vec result;
		result.data[0] = data[0] - b;
		result.data[1] = data[1] - b;
		return result;
	}
	inline t_vec operator*(t_scalar b) {
		t_vec result;
		result.data[0] = data[0] * b;
		result.data[1] = data[1] * b;
		return result;
	}
	inline t_vec operator/(t_scalar b) {
		t_vec result;
		result.data[0] = data[0] / b;
		result.data[1] = data[1] / b;
		return result;
	}
	inline t_vec operator-() const {
		t_vec result;
		result.data[0] = -data[0];
		result.data[1] = -data[1];
		return result;
	}
	inline t_scalar &operator[](size_t i) { return data[i]; }

	inline bool operator==(const t_vec &b) const {
		for (size_t i = 0; i < t_size; i++) {
			if (!(data[i] == b.data[i])) { return false; }
		}
		return true;
	}
	inline bool operator<=(const t_vec &b) const {
		for (size_t i = 0; i < t_size; i++) {
			if (!(data[i] <= b.data[i])) { return false; }
		}
		return true;
	}
	inline bool operator>=(const t_vec &b) const {
		for (size_t i = 0; i < t_size; i++) {
			if (!(data[i] >= b.data[i])) { return false; }
		}
		return true;
	}
	inline bool operator<(const t_vec &b) const {
		for (size_t i = 0; i < t_size; i++) {
			if (!(data[i] < b.data[i])) { return false; }
		}
		return true;
	}
	inline bool operator>(const t_vec &b) const {
		for (size_t i = 0; i < t_size; i++) {
			if (!(data[i] > b.data[i])) { return false; }
		}
		return true;
	}
	inline bool operator!=(const t_vec &b) const {
		for (size_t i = 0; i < t_size; i++) {
			if (!(data[i] != b.data[i])) { return false; }
		}
		return true;
	}

	inline t_vec &operator+=(const t_vec &b) {
		for (size_t i = 0; i < t_size; i++) { data[i] = data[i] + b.data[i]; }
		return *this;
	}
	inline t_vec &operator-=(const t_vec &b) {
		for (size_t i = 0; i < t_size; i++) { data[i] = data[i] - b.data[i]; }
		return *this;
	}
	inline t_vec &operator*=(const t_vec &b) {
		for (size_t i = 0; i < t_size; i++) { data[i] = data[i] * b.data[i]; }
		return *this;
	}
	inline t_vec &operator/=(const t_vec &b) {
		for (size_t i = 0; i < t_size; i++) { data[i] = data[i] / b.data[i]; }
		return *this;
	}

	inline t_scalar magnitude() const {
		t_scalar sum = 0;
		for (size_t i = 0; i < t_size; i++) { sum += data[i] * data[i]; }
		return std::sqrt(sum);
	}
	inline t_vec normalize() {
		t_vec res = *this;
		t_scalar _length = magnitude();
		for (size_t i = 0; i < t_size; i++) { res.data[i] /= _length; }
		return res;
	}
	inline t_scalar dot(const t_vec &b) {
		t_scalar result = 0;
		for (size_t i = 0; i < t_size; i++) { result += data[i] * b.data[i]; }
		return result;
	}
	inline t_scalar angle(const t_vec &b) {
		return std::acos(dot(b) / (magnitude() * b.magnitude()));
	}
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

	vec(std::initializer_list<int> list) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) 0; }
		if (list.size() == t_size) {
			auto initializer = list.begin();
			for (size_t i = 0; i < t_size; i++) {
				data[i] = (t_scalar) initializer[i];
			}
		}
	}
	vec(std::initializer_list<float> list) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) 0; }
		if (list.size() == t_size) {
			auto initializer = list.begin();
			for (size_t i = 0; i < t_size; i++) {
				data[i] = (t_scalar) initializer[i];
			}
		}
	}
	vec(std::initializer_list<double> list) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) 0; }
		if (list.size() == t_size) {
			auto initializer = list.begin();
			for (size_t i = 0; i < t_size; i++) {
				data[i] = (t_scalar) initializer[i];
			}
		}
	}
	vec(std::initializer_list<unsigned int> list) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) 0; }
		if (list.size() == t_size) {
			auto initializer = list.begin();
			for (size_t i = 0; i < t_size; i++) {
				data[i] = (t_scalar) initializer[i];
			}
		}
	}
	vec(int s) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) s; }
	}
	vec(float s) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) s; }
	}
	vec(double s) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) s; }
	}
	vec(unsigned int s) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) s; }
	}
	vec() {
		for (size_t i = 0; i < t_size; i++) { data[i] = t_scalar(); }
	}
	~vec() {}

	vec(t_scalar x, t_scalar y, t_scalar z) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
	}

	inline t_vec &operator=(std::initializer_list<t_scalar> list) {
		if (list.size() == t_size) {
			auto initializer = list.begin();
			for (size_t i = 0; i < t_size; i++) { data[i] = initializer[i]; }
		}
		return *this;
	}
	template<typename t_b_type>
	inline t_vec operator=(const t_b_type &b) {
		size_t l = (t_size < t_b_type::t_size) ? t_size : t_b_type::t_size;
		for (size_t i = 0; i < t_size; i++) { data[i] = t_scalar(b.data[i]); }
		for (size_t i = l; i < t_size; i++) { data[i] = t_scalar(0); }
		return *this;
	}

	inline t_vec operator+(const t_vec &b) {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) {
			result.data[i] = data[i] + b.data[i];
		}
		return result;
	}
	inline t_vec operator-(const t_vec &b) {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) {
			result.data[i] = data[i] - b.data[i];
		}
		return result;
	}
	inline t_vec operator/(const t_vec &b) {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) {
			result.data[i] = data[i] / b.data[i];
		}
		return result;
	}
	inline t_vec operator*(const t_vec &b) {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) {
			result.data[i] = data[i] * b.data[i];
		}
		return result;
	}
	inline t_vec operator+(t_scalar b) {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) { result.data[i] = data[i] + b; }
		return result;
	}
	inline t_vec operator-(t_scalar b) {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) { result.data[i] = data[i] - b; }
		return result;
	}
	inline t_vec operator*(t_scalar b) {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) { result.data[i] = data[i] * b; }
		return result;
	}
	inline t_vec operator/(t_scalar b) {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) { result.data[i] = data[i] / b; }
		return result;
	}
	inline t_vec operator-() const {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) { result.data[i] = -data[i]; }
		return result;
	}
	inline t_scalar &operator[](size_t i) { return data[i]; }

	inline bool operator==(const t_vec &b) const {
		for (size_t i = 0; i < t_size; i++) {
			if (!(data[i] == b.data[i])) { return false; }
		}
		return true;
	}
	inline bool operator<=(const t_vec &b) const {
		for (size_t i = 0; i < t_size; i++) {
			if (!(data[i] <= b.data[i])) { return false; }
		}
		return true;
	}
	inline bool operator>=(const t_vec &b) const {
		for (size_t i = 0; i < t_size; i++) {
			if (!(data[i] >= b.data[i])) { return false; }
		}
		return true;
	}
	inline bool operator<(const t_vec &b) const {
		for (size_t i = 0; i < t_size; i++) {
			if (!(data[i] < b.data[i])) { return false; }
		}
		return true;
	}
	inline bool operator>(const t_vec &b) const {
		for (size_t i = 0; i < t_size; i++) {
			if (!(data[i] > b.data[i])) { return false; }
		}
		return true;
	}
	inline bool operator!=(const t_vec &b) const {
		for (size_t i = 0; i < t_size; i++) {
			if (!(data[i] != b.data[i])) { return false; }
		}
		return true;
	}

	inline t_vec &operator+=(const t_vec &b) {
		for (size_t i = 0; i < t_size; i++) { data[i] = data[i] + b.data[i]; }
		return *this;
	}
	inline t_vec &operator-=(const t_vec &b) {
		for (size_t i = 0; i < t_size; i++) { data[i] = data[i] - b.data[i]; }
		return *this;
	}
	inline t_vec &operator*=(const t_vec &b) {
		for (size_t i = 0; i < t_size; i++) { data[i] = data[i] * b.data[i]; }
		return *this;
	}
	inline t_vec &operator/=(const t_vec &b) {
		for (size_t i = 0; i < t_size; i++) { data[i] = data[i] / b.data[i]; }
		return *this;
	}

	inline t_scalar magnitude() const {
		t_scalar sum = 0;
		for (size_t i = 0; i < t_size; i++) { sum += data[i] * data[i]; }
		return std::sqrt(sum);
	}
	inline t_vec normalize() {
		t_vec res = *this;
		t_scalar _length = magnitude();
		for (size_t i = 0; i < t_size; i++) { res.data[i] /= _length; }
		return res;
	}
	inline t_scalar dot(const t_vec &b) {
		t_scalar result = 0;
		for (size_t i = 0; i < t_size; i++) { result += data[i] * b.data[i]; }
		return result;
	}
	inline t_scalar angle(const t_vec &b) {
		return std::acos(dot(b) / (magnitude() * b.magnitude()));
	}

	inline t_vec cross(const t_vec &b) const {
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

	vec(std::initializer_list<int> list) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) 0; }
		if (list.size() == t_size) {
			auto initializer = list.begin();
			for (size_t i = 0; i < t_size; i++) {
				data[i] = (t_scalar) initializer[i];
			}
		}
	}
	vec(std::initializer_list<float> list) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) 0; }
		if (list.size() == t_size) {
			auto initializer = list.begin();
			for (size_t i = 0; i < t_size; i++) {
				data[i] = (t_scalar) initializer[i];
			}
		}
	}
	vec(std::initializer_list<double> list) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) 0; }
		if (list.size() == t_size) {
			auto initializer = list.begin();
			for (size_t i = 0; i < t_size; i++) {
				data[i] = (t_scalar) initializer[i];
			}
		}
	}
	vec(std::initializer_list<unsigned int> list) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) 0; }
		if (list.size() == t_size) {
			auto initializer = list.begin();
			for (size_t i = 0; i < t_size; i++) {
				data[i] = (t_scalar) initializer[i];
			}
		}
	}
	vec(int s) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) s; }
	}
	vec(float s) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) s; }
	}
	vec(double s) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) s; }
	}
	vec(unsigned int s) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) s; }
	}
	vec() {
		for (size_t i = 0; i < t_size; i++) { data[i] = t_scalar(); }
	}
	~vec() {}

	vec(t_scalar x, t_scalar y, t_scalar z, t_scalar w) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
		data[3] = w;
	}

	inline t_vec &operator=(std::initializer_list<t_scalar> list) {
		if (list.size() == t_size) {
			auto initializer = list.begin();
			for (size_t i = 0; i < t_size; i++) { data[i] = initializer[i]; }
		}
		return *this;
	}
	template<typename t_b_type>
	inline t_vec operator=(const t_b_type &b) {
		size_t l = (t_size < t_b_type::t_size) ? t_size : t_b_type::t_size;
		for (size_t i = 0; i < t_size; i++) { data[i] = t_scalar(b.data[i]); }
		for (size_t i = l; i < t_size; i++) { data[i] = t_scalar(0); }
		return *this;
	}

	inline t_vec operator+(const t_vec &b) {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) {
			result.data[i] = data[i] + b.data[i];
		}
		return result;
	}
	inline t_vec operator-(const t_vec &b) {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) {
			result.data[i] = data[i] - b.data[i];
		}
		return result;
	}
	inline t_vec operator/(const t_vec &b) {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) {
			result.data[i] = data[i] / b.data[i];
		}
		return result;
	}
	inline t_vec operator*(const t_vec &b) {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) {
			result.data[i] = data[i] * b.data[i];
		}
		return result;
	}
	inline t_vec operator+(t_scalar b) {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) { result.data[i] = data[i] + b; }
		return result;
	}
	inline t_vec operator-(t_scalar b) {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) { result.data[i] = data[i] - b; }
		return result;
	}
	inline t_vec operator*(t_scalar b) {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) { result.data[i] = data[i] * b; }
		return result;
	}
	inline t_vec operator/(t_scalar b) {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) { result.data[i] = data[i] / b; }
		return result;
	}
	inline t_vec operator-() const {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) { result.data[i] = -data[i]; }
		return result;
	}
	inline t_scalar &operator[](size_t i) { return data[i]; }

	inline bool operator==(const t_vec &b) const {
		for (size_t i = 0; i < t_size; i++) {
			if (!(data[i] == b.data[i])) { return false; }
		}
		return true;
	}

	inline bool operator<=(const t_vec &b) const {
		for (size_t i = 0; i < t_size; i++) {
			if (!(data[i] <= b.data[i])) { return false; }
		}
		return true;
	}

	inline bool operator>=(const t_vec &b) const {
		for (size_t i = 0; i < t_size; i++) {
			if (!(data[i] >= b.data[i])) { return false; }
		}
		return true;
	}

	inline bool operator<(const t_vec &b) const {
		for (size_t i = 0; i < t_size; i++) {
			if (!(data[i] < b.data[i])) { return false; }
		}
		return true;
	}

	inline bool operator>(const t_vec &b) const {
		for (size_t i = 0; i < t_size; i++) {
			if (!(data[i] > b.data[i])) { return false; }
		}
		return true;
	}

	inline bool operator!=(const t_vec &b) const {
		for (size_t i = 0; i < t_size; i++) {
			if (!(data[i] != b.data[i])) { return false; }
		}
		return true;
	}

	inline t_vec &operator+=(const t_vec &b) {
		for (size_t i = 0; i < t_size; i++) { data[i] = data[i] + b.data[i]; }
		return *this;
	}

	inline t_vec &operator-=(const t_vec &b) {
		for (size_t i = 0; i < t_size; i++) { data[i] = data[i] - b.data[i]; }
		return *this;
	}

	inline t_vec &operator*=(const t_vec &b) {
		for (size_t i = 0; i < t_size; i++) { data[i] = data[i] * b.data[i]; }
		return *this;
	}

	inline t_vec &operator/=(const t_vec &b) {
		for (size_t i = 0; i < t_size; i++) { data[i] = data[i] / b.data[i]; }
		return *this;
	}

	inline t_scalar magnitude() const {
		t_scalar sum = 0;
		for (size_t i = 0; i < t_size; i++) { sum += data[i] * data[i]; }
		return std::sqrt(sum);
	}

	inline t_vec normalize() {
		t_vec res = *this;
		t_scalar _length = magnitude();
		for (size_t i = 0; i < t_size; i++) { res.data[i] /= _length; }
		return res;
	}

	inline t_scalar dot(const t_vec &b) {
		t_scalar result = 0;
		for (size_t i = 0; i < t_size; i++) { result += data[i] * b.data[i]; }
		return result;
	}

	inline t_scalar angle(const t_vec &b) {
		return std::acos(dot(b) / (magnitude() * b.magnitude()));
	}

	inline t_vec cross(const t_vec &b) const {
		return {y() * b.z() - z() * b.y(), z() * b.x() - x() * b.z(),
				x() * b.y() - y() * b.x(), 1.f};
	}
};

//generic non SIMD vector template
template<typename t_scalar_, size_t t_size_>
struct vec<t_scalar_, t_size_, false> {
	MD_MATH_VEC_DEFINES(t_size_, false)
	t_scalar data[t_size];

	MD_MATH_ALIAS(x, 0)
	MD_MATH_ALIAS(y, 1)
	MD_MATH_ALIAS(z, 2)
	MD_MATH_ALIAS(w, 3)

	MD_MATH_ALIAS(r, 0)
	MD_MATH_ALIAS(g, 1)
	MD_MATH_ALIAS(b, 2)
	MD_MATH_ALIAS(a, 3)

	vec(std::initializer_list<int> list) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) 0; }
		if (list.size() == t_size) {
			auto initializer = list.begin();
			for (size_t i = 0; i < t_size; i++) {
				data[i] = (t_scalar) initializer[i];
			}
		}
	}
	vec(std::initializer_list<float> list) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) 0; }
		if (list.size() == t_size) {
			auto initializer = list.begin();
			for (size_t i = 0; i < t_size; i++) {
				data[i] = (t_scalar) initializer[i];
			}
		}
	}
	vec(std::initializer_list<double> list) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) 0; }
		if (list.size() == t_size) {
			auto initializer = list.begin();
			for (size_t i = 0; i < t_size; i++) {
				data[i] = (t_scalar) initializer[i];
			}
		}
	}
	vec(std::initializer_list<unsigned int> list) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) 0; }
		if (list.size() == t_size) {
			auto initializer = list.begin();
			for (size_t i = 0; i < t_size; i++) {
				data[i] = (t_scalar) initializer[i];
			}
		}
	}

	vec(int s) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) s; }
	}

	vec(float s) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) s; }
	}

	vec(double s) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) s; }
	}

	vec(unsigned int s) {
		for (size_t i = 0; i < t_size; i++) { data[i] = (t_scalar) s; }
	}

	vec() {
		for (size_t i = 0; i < t_size; i++) { data[i] = t_scalar(); }
	}

	~vec() {}

	inline t_vec &operator=(std::initializer_list<t_scalar> list) {
		if (list.size() == t_size) {
			auto initializer = list.begin();
			for (size_t i = 0; i < t_size; i++) { data[i] = initializer[i]; }
		}
		return *this;
	}

	template<typename t_b_type>
	inline t_vec operator=(const t_b_type &b) {
		size_t l = (t_size < t_b_type::t_size) ? t_size : t_b_type::t_size;
		for (size_t i = 0; i < t_size; i++) { data[i] = t_scalar(b.data[i]); }
		for (size_t i = l; i < t_size; i++) { data[i] = t_scalar(0); }
		return *this;
	}

	inline t_vec operator+(const t_vec &b) {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) {
			result.data[i] = data[i] + b.data[i];
		}
		return result;
	}

	inline t_vec operator-(const t_vec &b) {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) {
			result.data[i] = data[i] - b.data[i];
		}
		return result;
	}

	inline t_vec operator/(const t_vec &b) {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) {
			result.data[i] = data[i] / b.data[i];
		}
		return result;
	}

	inline t_vec operator*(const t_vec &b) {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) {
			result.data[i] = data[i] * b.data[i];
		}
		return result;
	}

	inline t_vec operator+(t_scalar b) {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) { result.data[i] = data[i] + b; }
		return result;
	}

	inline t_vec operator-(t_scalar b) {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) { result.data[i] = data[i] - b; }
		return result;
	}

	inline t_vec operator*(t_scalar b) {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) { result.data[i] = data[i] * b; }
		return result;
	}

	inline t_vec operator/(t_scalar b) {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) { result.data[i] = data[i] / b; }
		return result;
	}

	inline t_vec operator-() const {
		t_vec result;
		for (size_t i = 0; i < t_size; i++) { result.data[i] = -data[i]; }
		return result;
	}

	inline t_scalar &operator[](size_t i) { return data[i]; }

	inline bool operator==(const t_vec &b) const {
		for (size_t i = 0; i < t_size; i++) {
			if (!(data[i] == b.data[i])) { return false; }
		}
		return true;
	}

	inline bool operator<=(const t_vec &b) const {
		for (size_t i = 0; i < t_size; i++) {
			if (!(data[i] <= b.data[i])) { return false; }
		}
		return true;
	}

	inline bool operator>=(const t_vec &b) const {
		for (size_t i = 0; i < t_size; i++) {
			if (!(data[i] >= b.data[i])) { return false; }
		}
		return true;
	}

	inline bool operator<(const t_vec &b) const {
		for (size_t i = 0; i < t_size; i++) {
			if (!(data[i] < b.data[i])) { return false; }
		}
		return true;
	}

	inline bool operator>(const t_vec &b) const {
		for (size_t i = 0; i < t_size; i++) {
			if (!(data[i] > b.data[i])) { return false; }
		}
		return true;
	}

	inline bool operator!=(const t_vec &b) const {
		for (size_t i = 0; i < t_size; i++) {
			if (!(data[i] != b.data[i])) { return false; }
		}
		return true;
	}

	inline t_vec &operator+=(const t_vec &b) {
		for (size_t i = 0; i < t_size; i++) { data[i] = data[i] + b.data[i]; }
		return *this;
	}

	inline t_vec &operator-=(const t_vec &b) {
		for (size_t i = 0; i < t_size; i++) { data[i] = data[i] - b.data[i]; }
		return *this;
	}

	inline t_vec &operator*=(const t_vec &b) {
		for (size_t i = 0; i < t_size; i++) { data[i] = data[i] * b.data[i]; }
		return *this;
	}

	inline t_vec &operator/=(const t_vec &b) {
		for (size_t i = 0; i < t_size; i++) { data[i] = data[i] / b.data[i]; }
		return *this;
	}

	inline t_scalar magnitude() const {
		t_scalar sum = 0;
		for (size_t i = 0; i < t_size; i++) { sum += data[i] * data[i]; }
		return std::sqrt(sum);
	}

	inline t_vec normalize() {
		t_vec res = *this;
		t_scalar _length = magnitude();
		for (size_t i = 0; i < t_size; i++) { res.data[i] /= _length; }
		return res;
	}

	inline t_scalar dot(const t_vec &b) {
		t_scalar result = 0;
		for (size_t i = 0; i < t_size; i++) { result += data[i] * b.data[i]; }
		return result;
	}

	inline t_scalar angle(const t_vec &b) {
		return std::acos(dot(b) / (magnitude() * b.magnitude()));
	}
};

//SIMD vectors
template<>
struct alignas(16) vec<float, 4, true> {
	static constexpr size_t t_size = 4;
	static constexpr bool t_simd = true;
	typedef vec<float, t_size, t_simd> t_vec;
	typedef float t_scalar;

	union {
		__m128 data_v;
		float data[4];
	};

	MD_MATH_ALIAS(x, 0);
	MD_MATH_ALIAS(y, 1);
	MD_MATH_ALIAS(z, 2);
	MD_MATH_ALIAS(w, 3);

	vec() { data_v = _mm_set1_ps(0.f); }
	vec(float s) { data_v = _mm_set1_ps(s); }
	vec(float x, float y, float z, float w) { data_v = {x, y, z, w}; }
	vec(const __m128 &v) { data_v = v; }
	vec(const vec<float, 4, false> &v) {
		data_v = {v.x(), v.y(), v.z(), v.w()};
	}
	~vec() {}

	inline operator __m128() { return data_v; }

	inline t_vec &operator=(const __m128 &v) {
		data_v = v;
		return *this;
	}
	inline t_vec &operator=(const vec<float, 4, false> &v) {
		data_v = {v.x(), v.y(), v.z(), v.w()};
		return *this;
	}


	inline t_vec operator-() {
		__m128 mask = _mm_castsi128_ps(_mm_set1_epi32(~0x7FFFFFFF));
		return _mm_xor_ps(data_v, mask);
	}

	inline t_vec operator+(const t_vec &v) {
		return _mm_add_ps(data_v, v.data_v);
	}
	inline t_vec operator-(const t_vec &v) {
		return _mm_sub_ps(data_v, v.data_v);
	}
	inline t_vec operator*(const t_vec &v) {
		return _mm_mul_ps(data_v, v.data_v);
	}
	inline t_vec operator/(const t_vec &v) {
		return _mm_div_ps(data_v, v.data_v);
	}

	inline t_vec compare_eq(const t_vec &v) {
		t_vec cmp = _mm_cmpeq_ps(data_v, v.data_v);
		return _mm_and_ps(cmp, t_vec(1.0f));
	}
	inline t_vec compare_neq(const t_vec &v) {
		t_vec cmp = _mm_cmpneq_ps(data_v, v.data_v);
		return _mm_and_ps(cmp, t_vec(1.0f));
	}
	inline t_vec compare_le(const t_vec &v) {
		t_vec cmp = _mm_cmple_ps(data_v, v.data_v);
		return _mm_and_ps(cmp, t_vec(1.0f));
	}
	inline t_vec compare_ge(const t_vec &v) {
		t_vec cmp = _mm_cmpge_ps(data_v, v.data_v);
		return _mm_and_ps(cmp, t_vec(1.0f));
	}
	inline t_vec compare_lt(const t_vec &v) {
		t_vec cmp = _mm_cmplt_ps(data_v, v.data_v);
		return _mm_and_ps(cmp, t_vec(1.0f));
	}
	inline t_vec compare_gt(const t_vec &v) {
		t_vec cmp = _mm_cmpgt_ps(data_v, v.data_v);
		return _mm_and_ps(cmp, t_vec(1.0f));
	}

	inline bool operator==(const t_vec &v) {
		t_vec cmp = _mm_cmpeq_ps(data_v, v.data_v);
		return !(cmp.x() || cmp.y() || cmp.z() || cmp.w());
	}
	inline bool operator!=(const t_vec &v) {
		t_vec cmp = _mm_cmpneq_ps(data_v, v.data_v);
		return !(cmp.x() || cmp.y() || cmp.z() || cmp.w());
	}
	inline bool operator<=(const t_vec &v) {
		t_vec cmp = _mm_cmple_ps(data_v, v.data_v);
		return !(cmp.x() || cmp.y() || cmp.z() || cmp.w());
	}
	inline bool operator>=(const t_vec &v) {
		t_vec cmp = _mm_cmpge_ps(data_v, v.data_v);
		return !(cmp.x() || cmp.y() || cmp.z() || cmp.w());
	}
	inline bool operator<(const t_vec &v) {
		t_vec cmp = _mm_cmplt_ps(data_v, v.data_v);
		return !(cmp.x() || cmp.y() || cmp.z() || cmp.w());
	}
	inline bool operator>(const t_vec &v) {
		t_vec cmp = _mm_cmpgt_ps(data_v, v.data_v);
		return !(cmp.x() || cmp.y() || cmp.z() || cmp.w());
	}

	inline t_vec operator+=(const t_vec &v) {
		return data_v = _mm_add_ps(data_v, v.data_v);
	}
	inline t_vec operator-=(const t_vec &v) {
		return data_v = _mm_sub_ps(data_v, v.data_v);
	}
	inline t_vec operator*=(const t_vec &v) {
		return data_v = _mm_mul_ps(data_v, v.data_v);
	}
	inline t_vec operator/=(const t_vec &v) {
		return data_v = _mm_div_ps(data_v, v.data_v);
	}

	inline t_scalar sum() { return data[0] + data[1] + data[2] + data[3]; }
	inline t_scalar dot(const t_vec &v) const {
		const __m128 v0 = _mm_mul_ps(data_v, v.data_v);
		return t_vec(v0).sum();
	}
	inline t_vec cross(const t_vec &v) const {
		const __m128 t1 = _mm_shuffle_ps(
				data_v, data_v, MD_SHUFFLE(MD_S_Y, MD_S_Z, MD_S_X, MD_S_W));
		const __m128 t2 = _mm_shuffle_ps(
				v.data_v, v.data_v, MD_SHUFFLE(MD_S_Z, MD_S_X, MD_S_Y, MD_S_W));
		const __m128 t3 = _mm_shuffle_ps(
				data_v, data_v, MD_SHUFFLE(MD_S_Z, MD_S_X, MD_S_Y, MD_S_W));
		const __m128 t4 = _mm_shuffle_ps(
				v.data_v, v.data_v, MD_SHUFFLE(MD_S_Y, MD_S_Z, MD_S_X, MD_S_W));

		return _mm_sub_ps(_mm_mul_ps(t1, t2), _mm_mul_ps(t3, t4));
	}
	inline t_scalar magnitude() const {
		__m128 res = {x(), y(), z(), 0.f};
		return std::sqrt(t_vec(_mm_mul_ps(res, res)).sum());
	}
	inline t_scalar magnitude4d() const { return std::sqrt(dot(*this)); }
	inline t_vec normalize() { return _mm_div_ps(data_v, t_vec(magnitude())); }
	inline t_vec normalize4d() {
		return _mm_div_ps(data_v, t_vec(magnitude4d()));
	}
	inline t_scalar angle(const t_vec &v) {
		return std::acos(dot(v) / (magnitude() * v.magnitude()));
	}
};

template<>
struct alignas(16) vec<double, 2, true> {
	static constexpr size_t t_size = 2;
	static constexpr bool t_simd = true;
	typedef vec<double, t_size, t_simd> t_vec;
	typedef double t_scalar;

	union {
		__m128d data_v;
		double data[2];
	};

	MD_MATH_ALIAS(x, 0);
	MD_MATH_ALIAS(y, 1);

	vec() { data_v = _mm_set1_pd(0.0); }
	vec(double s) { data_v = _mm_set1_pd(s); }
	vec(double x, double y) { data_v = _mm_set_pd(y, x); }
	vec(const __m128d &v) { data_v = v; }
	~vec() {}

	inline operator __m128d() { return data_v; }

	inline t_vec &operator=(const __m128d &v) {
		data_v = v;
		return *this;
	}

	inline t_vec operator-() {
		__m128d mask = _mm_castsi128_pd(_mm_set1_epi64x(~0x7FFFFFFFFFFFFFFF));
		return _mm_xor_pd(data_v, mask);
	}

	inline t_vec operator+(const t_vec &v) {
		return _mm_add_pd(data_v, v.data_v);
	}
	inline t_vec operator-(const t_vec &v) {
		return _mm_sub_pd(data_v, v.data_v);
	}
	inline t_vec operator*(const t_vec &v) {
		return _mm_mul_pd(data_v, v.data_v);
	}
	inline t_vec operator/(const t_vec &v) {
		return _mm_div_pd(data_v, v.data_v);
	}

	inline t_vec compare_eq(const t_vec &v) {
		__m128d cmp = _mm_cmpeq_pd(data_v, v.data_v);
		return t_vec(_mm_and_pd(cmp, _mm_set1_pd(1.0)));
	}
	inline t_vec compare_neq(const t_vec &v) {
		__m128d cmp = _mm_cmpneq_pd(data_v, v.data_v);
		return t_vec(_mm_and_pd(cmp, _mm_set1_pd(1.0)));
	}
	inline t_vec compare_le(const t_vec &v) {
		__m128d cmp = _mm_cmple_pd(data_v, v.data_v);
		return t_vec(_mm_and_pd(cmp, _mm_set1_pd(1.0)));
	}
	inline t_vec compare_ge(const t_vec &v) {
		__m128d cmp = _mm_cmpge_pd(data_v, v.data_v);
		return t_vec(_mm_and_pd(cmp, _mm_set1_pd(1.0)));
	}
	inline t_vec compare_lt(const t_vec &v) {
		__m128d cmp = _mm_cmplt_pd(data_v, v.data_v);
		return t_vec(_mm_and_pd(cmp, _mm_set1_pd(1.0)));
	}
	inline t_vec compare_gt(const t_vec &v) {
		__m128d cmp = _mm_cmpgt_pd(data_v, v.data_v);
		return t_vec(_mm_and_pd(cmp, _mm_set1_pd(1.0)));
	}

	inline bool operator==(const t_vec &v) {
		t_vec cmp = _mm_cmpeq_pd(data_v, v.data_v);
		return !(cmp.x() || cmp.y());
	}
	inline bool operator!=(const t_vec &v) {
		t_vec cmp = _mm_cmpneq_pd(data_v, v.data_v);
		return !(cmp.x() || cmp.y());
	}
	inline bool operator<=(const t_vec &v) {
		t_vec cmp = _mm_cmple_pd(data_v, v.data_v);
		return !(cmp.x() || cmp.y());
	}
	inline bool operator>=(const t_vec &v) {
		t_vec cmp = _mm_cmpge_pd(data_v, v.data_v);
		return !(cmp.x() || cmp.y());
	}
	inline bool operator<(const t_vec &v) {
		t_vec cmp = _mm_cmplt_pd(data_v, v.data_v);
		return !(cmp.x() || cmp.y());
	}
	inline bool operator>(const t_vec &v) {
		t_vec cmp = _mm_cmpgt_pd(data_v, v.data_v);
		return !(cmp.x() || cmp.y());
	}

	inline t_vec operator+=(const t_vec &v) {
		return data_v = _mm_add_pd(data_v, v.data_v);
	}
	inline t_vec operator-=(const t_vec &v) {
		return data_v = _mm_sub_pd(data_v, v.data_v);
	}
	inline t_vec operator*=(const t_vec &v) {
		return data_v = _mm_mul_pd(data_v, v.data_v);
	}
	inline t_vec operator/=(const t_vec &v) {
		return data_v = _mm_div_pd(data_v, v.data_v);
	}

	inline t_scalar sum() { return data[0] + data[1]; }
	inline t_scalar dot(const t_vec &v) const {
		const __m128d v0 = _mm_mul_pd(data_v, v.data_v);
		return t_vec(v0).sum();
	}
	inline t_scalar magnitude() const { return std::sqrt(dot(*this)); }
	inline t_vec normalize() { return _mm_div_pd(data_v, t_vec(magnitude())); }

	inline t_scalar angle(const t_vec &v) {
		return std::acos(dot(v) / (magnitude() * v.magnitude()));
	}
};

template<>
struct alignas(32) vec<double, 4, true> {
	static constexpr size_t t_size = 4;
	static constexpr bool t_simd = true;
	typedef vec<double, t_size, t_simd> t_vec;
	typedef double t_scalar;
	union {
		__m256d data_v;
		double data[4];
	};

	MD_MATH_ALIAS(x, 0);
	MD_MATH_ALIAS(y, 1);
	MD_MATH_ALIAS(z, 2);
	MD_MATH_ALIAS(w, 3);

	vec() { data_v = _mm256_set1_pd(0.0); }
	vec(double s) { data_v = _mm256_set1_pd(s); }
	vec(double x, float y, float z, float w) { data_v = {x, y, z, w}; }
	vec(const __m256d &v) { data_v = v; }
	vec(const vec<double, 4, false> &v) {
		data_v = {v.x(), v.y(), v.z(), v.w()};
	}
	~vec() {}

	inline operator __m256d() { return data_v; }

	inline t_vec &operator=(const __m256d &v) { data_v = v; }
	inline t_vec &operator=(const vec<double, 4, false> &v) {
		data_v = {v.x(), v.y(), v.z(), v.w()};
	}

	inline t_vec operator-() {
		__m256d mask =
				_mm256_castsi256_pd(_mm256_set1_epi64x(~0x7FFFFFFFFFFFFFFF));
		return _mm256_xor_pd(data_v, mask);
	}

	inline t_vec operator+(const t_vec &v) {
		return _mm256_add_pd(data_v, v.data_v);
	}
	inline t_vec operator-(const t_vec &v) {
		return _mm256_sub_pd(data_v, v.data_v);
	}
	inline t_vec operator*(const t_vec &v) {
		return _mm256_mul_pd(data_v, v.data_v);
	}
	inline t_vec operator/(const t_vec &v) {
		return _mm256_div_pd(data_v, v.data_v);
	}

	inline t_vec compare_eq(const t_vec &v) {
		__m256d cmp = _mm256_cmp_pd(data_v, v.data_v, _CMP_EQ_OQ);
		return t_vec(cmp);
	}
	inline t_vec compare_neq(const t_vec &v) {
		__m256d cmp = _mm256_cmp_pd(data_v, v.data_v, _CMP_NEQ_OQ);
		return t_vec(cmp);
	}
	inline t_vec compare_le(const t_vec &v) {
		__m256d cmp = _mm256_cmp_pd(data_v, v.data_v, _CMP_LE_OQ);
		return t_vec(cmp);
	}
	inline t_vec compare_ge(const t_vec &v) {
		__m256d cmp = _mm256_cmp_pd(data_v, v.data_v, _CMP_GE_OQ);
		return t_vec(cmp);
	}
	inline t_vec compare_lt(const t_vec &v) {
		__m256d cmp = _mm256_cmp_pd(data_v, v.data_v, _CMP_LT_OQ);
		return t_vec(cmp);
	}
	inline t_vec compare_gt(const t_vec &v) {
		__m256d cmp = _mm256_cmp_pd(data_v, v.data_v, _CMP_GT_OQ);
		return t_vec(cmp);
	}

	inline bool operator==(const t_vec &v) {
		t_vec cmp = _mm256_cmp_pd(data_v, v.data_v, _CMP_EQ_OQ);
		return !(cmp.x() || cmp.y() || cmp.z() || cmp.w());
	}
	inline bool operator!=(const t_vec &v) {
		t_vec cmp = _mm256_cmp_pd(data_v, v.data_v, _CMP_NEQ_OQ);
		return !(cmp.x() || cmp.y() || cmp.z() || cmp.w());
	}
	inline bool operator<=(const t_vec &v) {
		t_vec cmp = _mm256_cmp_pd(data_v, v.data_v, _CMP_LE_OQ);
		return !(cmp.x() || cmp.y() || cmp.z() || cmp.w());
	}
	inline bool operator>=(const t_vec &v) {
		t_vec cmp = _mm256_cmp_pd(data_v, v.data_v, _CMP_GE_OQ);
		return !(cmp.x() || cmp.y() || cmp.z() || cmp.w());
	}
	inline bool operator<(const t_vec &v) {
		t_vec cmp = _mm256_cmp_pd(data_v, v.data_v, _CMP_LT_OQ);
		return !(cmp.x() || cmp.y() || cmp.z() || cmp.w());
	}
	inline bool operator>(const t_vec &v) {
		t_vec cmp = _mm256_cmp_pd(data_v, v.data_v, _CMP_GT_OQ);
		return !(cmp.x() || cmp.y() || cmp.z() || cmp.w());
	}

	inline t_vec operator+=(const t_vec &v) {
		return data_v = _mm256_add_pd(data_v, v.data_v);
	}
	inline t_vec operator-=(const t_vec &v) {
		return data_v = _mm256_sub_pd(data_v, v.data_v);
	}
	inline t_vec operator*=(const t_vec &v) {
		return data_v = _mm256_mul_pd(data_v, v.data_v);
	}
	inline t_vec operator/=(const t_vec &v) {
		return data_v = _mm256_div_pd(data_v, v.data_v);
	}

	inline t_scalar sum() { return data[0] + data[1] + data[2] + data[3]; }
	inline t_scalar dot(const t_vec &v) const {
		const __m256d v0 = _mm256_mul_pd(data_v, v.data_v);
		return t_vec(v0).sum();
	}
	inline t_vec cross(const t_vec &v) const {
		const __m256d t1 = _mm256_permute4x64_pd(
				data_v, MD_SHUFFLE(MD_S_Y, MD_S_Z, MD_S_X, MD_S_W));
		const __m256d t2 = _mm256_permute4x64_pd(
				v.data_v, MD_SHUFFLE(MD_S_Z, MD_S_X, MD_S_Y, MD_S_W));
		const __m256d t3 = _mm256_permute4x64_pd(
				data_v, MD_SHUFFLE(MD_S_Z, MD_S_X, MD_S_Y, MD_S_W));
		const __m256d t4 = _mm256_permute4x64_pd(
				v.data_v, MD_SHUFFLE(MD_S_Y, MD_S_Z, MD_S_X, MD_S_W));

		return _mm256_sub_pd(_mm256_mul_pd(t1, t2), _mm256_mul_pd(t3, t4));
	}
	inline t_scalar magnitude() const {
		__m256d res = {x(), y(), z(), 0.0};
		return std::sqrt(t_vec(_mm256_mul_pd(res, res)).sum());
	}
	inline t_scalar magnitude4d() const { return std::sqrt(dot(*this)); }
	inline t_vec normalize() {
		return _mm256_div_pd(data_v, t_vec(magnitude()));
	}
	inline t_vec normalize4d() {
		return _mm256_div_pd(data_v, t_vec(magnitude4d()));
	}

	inline t_scalar angle(const t_vec &v) {
		return std::acos(dot(v) / (magnitude() * v.magnitude()));
	}
};

typedef vec<unsigned int, 2, false> uvec2_s;
typedef vec<unsigned int, 3, false> uvec3_s;
typedef vec<unsigned int, 4, false> uvec4_s;

typedef vec<int, 2, false> ivec2_s;
typedef vec<int, 3, false> ivec3_s;
typedef vec<int, 4, false> ivec4_s;

typedef vec<float, 2, false> vec2_s;
typedef vec<float, 3, false> vec3_s;
typedef vec<float, 4, false> vec4_s, quat_s;

typedef vec<double, 2, false> dvec2_s;
typedef vec<double, 3, false> dvec3_s;
typedef vec<double, 4, false> dvec4_s, dquat_s;

typedef vec<float, 4, true> vec4_v, quat_v;
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

#endif// VECTOR_H