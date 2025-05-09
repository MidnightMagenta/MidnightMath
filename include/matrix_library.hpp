#ifndef MATRIX_LIBRARY_H
#define MATRIX_LIBRARY_H

#include "../include/matrix.hpp"

namespace md_math {
template<typename t_matrix>
inline void RotationMatrixX(typename t_matrix::t_scalar angle,
							t_matrix *transform) {
	transform->SetIdentity();
	transform->columns[1].data[1] = std::cos(angle);
	transform->columns[1].data[2] = std::sin(angle);
	transform->columns[2].data[1] = -std::sin(angle);
	transform->columns[2].data[2] = std::cos(angle);
}

template<typename t_matrix>
inline t_matrix RotationMatrixX(typename t_matrix::t_scalar angle) {
	t_matrix result = result.SetIdentity();
	RotationMatrixX(angle, &result);
	return result;
}

template<typename t_matrix>
inline void RotationMatrixY(typename t_matrix::t_scalar angle,
							t_matrix *transform) {
	transform->SetIdentity();
	transform->columns[0].data[0] = std::cos(angle);
	transform->columns[0].data[2] = -std::sin(angle);
	transform->columns[2].data[0] = std::sin(angle);
	transform->columns[2].data[2] = std::cos(angle);
}

template<typename t_matrix>
inline t_matrix RotationMatrixY(typename t_matrix::t_scalar angle) {
	t_matrix result = result.SetIdentity();
	RotationMatrixY(angle, &result);
	return result;
}

template<typename t_matrix>
inline void RotationMatrixZ(typename t_matrix::t_scalar angle,
							t_matrix *transform) {
	transform->SetIdentity();
	transform->columns[0].data[0] = std::cos(angle);
	transform->columns[0].data[1] = std::sin(angle);
	transform->columns[1].data[0] = -std::sin(angle);
	transform->columns[1].data[1] = std::cos(angle);
}

template<typename t_matrix>
inline t_matrix RotationMatrixZ(typename t_matrix::t_scalar angle) {
	t_matrix result = result.SetIdentity();
	RotationMatrixZ(angle, &result);
	return result;
}

template<typename t_matrix>
inline t_matrix RotationMatrix(typename t_matrix::t_scalar x,
							   typename t_matrix::t_scalar y,
							   typename t_matrix::t_scalar z) {
	return RotationMatrixZ<t_matrix>(z) * RotationMatrixY<t_matrix>(y) *
		   RotationMatrixX<t_matrix>(x);
}

template<typename t_matrix>
inline void
TranslationMatrix(typename t_matrix::t_scalar x, typename t_matrix::t_scalar y,
				  typename t_matrix::t_scalar z, t_matrix *transform) {
	typename t_matrix::t_vec translation = {x, y, z, t_matrix::t_scalar(1.0)};
	transform->columns[3] = translation;
}

template<typename t_matrix>
inline t_matrix TranslationMatrix(typename t_matrix::t_scalar x,
								  typename t_matrix::t_scalar y,
								  typename t_matrix::t_scalar z) {
	t_matrix result = result.SetIdentity();
	TranslationMatrix(x, y, z, &result);
	return result;
}

template<typename t_matrix>
inline void ScaleMatrix(typename t_matrix::t_scalar x,
						typename t_matrix::t_scalar y,
						typename t_matrix::t_scalar z, t_matrix *transform) {
	transform->columns[0].data[0] = x;
	transform->columns[1].data[1] = y;
	transform->columns[2].data[2] = z;
}

template<typename t_matrix>
inline t_matrix ScaleMatrix(typename t_matrix::t_scalar x,
							typename t_matrix::t_scalar y,
							typename t_matrix::t_scalar z) {
	t_matrix result = result.SetIdentity();
	ScaleMatrix(x, y, z, &result);
	return result;
}

template<typename t_matrix>
inline void OrthographicProjectionMatrix(typename t_matrix::t_scalar l,
										 typename t_matrix::t_scalar r,
										 typename t_matrix::t_scalar b,
										 typename t_matrix::t_scalar t,
										 typename t_matrix::t_scalar n,
										 typename t_matrix::t_scalar f,
										 t_matrix *transform) {
	*transform = transform->SetIdentity();
	transform->columns[0].data[0] = 2 / (r - l);
	transform->columns[1].data[1] = 2 / (t - b);
	transform->columns[2].data[2] = -2 / (f - n);
	transform->columns[3] =
			t_matrix::t_vec({-((r + l) / (r - l)), -((t + b) / (t - b)),
							 -((f + n) / (f - n)), t_matrix::t_scalar(1.0)});
}

template<typename t_matrix>
inline t_matrix OrthographicProjectionMatrix(typename t_matrix::t_scalar l,
											 typename t_matrix::t_scalar r,
											 typename t_matrix::t_scalar b,
											 typename t_matrix::t_scalar t,
											 typename t_matrix::t_scalar n,
											 typename t_matrix::t_scalar f) {
	t_matrix result;
	OrthographicProjectionMatrix(l, r, b, t, n, f, &result);
	return result;
}

template<typename t_matrix>
inline void FrustrumProjectionMatrix(typename t_matrix::t_scalar fov,
									 typename t_matrix::t_scalar aspect,
									 typename t_matrix::t_scalar n,
									 typename t_matrix::t_scalar f,
									 t_matrix *transform) {
	*transform = transform->SetIdentity();
	transform->columns[0] = t_matrix::t_vec(
			{(2 * n) / (aspect * std::tan(fov / 2)), t_matrix::t_scalar(0),
			 t_matrix::t_scalar(0), t_matrix::t_scalar(0)});
	transform->columns[1] =
			t_matrix::t_vec({t_matrix::t_scalar(0), (2 * n) / std::tan(fov / 2),
							 t_matrix::t_scalar(0), t_matrix::t_scalar(0)});
	transform->columns[2] =
			t_matrix::t_vec({t_matrix::t_scalar(0), t_matrix::t_scalar(0),
							 -(f + n) / (f - n), t_matrix::t_scalar(-1)});
	transform->columns[3] =
			t_matrix::t_vec({t_matrix::t_scalar(0), t_matrix::t_scalar(0),
							 -(2 * f * n) / (f - n), t_matrix::t_scalar(0)});
}

template<typename t_matrix>
inline t_matrix FrustrumProjectionMatrix(typename t_matrix::t_scalar fov,
										 typename t_matrix::t_scalar aspect,
										 typename t_matrix::t_scalar n,
										 typename t_matrix::t_scalar f) {
	t_matrix result;
	FrustrumProjectionMatrix(fov, aspect, n, f, &result);
	return result;
}

template<typename t_matrix>
inline void LookAtMatrix(const typename t_matrix::t_vec &eye,
						 const typename t_matrix::t_vec &target,
						 const typename t_matrix::t_vec &up,
						 t_matrix *transform) {
	using t_vec = typename t_matrix::t_vec;
	using t_scalar = typename t_matrix::t_scalar;

	const t_vec c2 = (eye - target).normalize();
	const t_vec c0 = c2.cross(-up).normalize();
	const t_vec c1 = c2.cross(c0);
	const t_vec neg_eye = -eye;

	const t_scalar d0 = t_scalar(c0.dot(neg_eye));
	const t_scalar d1 = t_scalar(c1.dot(neg_eye));
	const t_scalar d2 = t_scalar(c2.dot(neg_eye));

	t_matrix result{};
	transform->SetIdentity();
	transform->columns[0] = c0;
	transform->columns[1] = c1;
	transform->columns[2] = c2;

	transform->columns[0].w() = d0;
	transform->columns[1].w() = d1;
	transform->columns[2].w() = d2;
	transform->SetTranspose();
}

template<typename t_matrix>
inline t_matrix LookAtMatrix(const typename t_matrix::t_vec &eye,
							 const typename t_matrix::t_vec &target,
							 const typename t_matrix::t_vec &up) {
	t_matrix result;
	LookAtMatrix(eye, target, up, &result);
	return result;
}

}// namespace md_math

#endif// !MATRIX_LIBRARY_H
