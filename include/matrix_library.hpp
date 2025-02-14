#ifndef MATRIX_LIBRARY_H
#define MATRIX_LIBRARY_H

#include "../include/matrix.hpp"

namespace md_math {
template<typename t_matrix>
inline t_matrix RotationMatrixX(typename t_matrix::t_scalar angle) {
	t_matrix result;
	result.SetIdentity();
	result.columns[1].data[1] = std::cos(angle);
	result.columns[1].data[2] = std::sin(angle);
	result.columns[2].data[1] = -std::sin(angle);
	result.columns[2].data[2] = std::cos(angle);
	return result;
}

template<typename t_matrix>
inline t_matrix RotationMatrixY(typename t_matrix::t_scalar angle) {
	t_matrix result;
	result.SetIdentity();
	result.columns[0].data[0] = std::cos(angle);
	result.columns[0].data[2] = -std::sin(angle);
	result.columns[2].data[0] = std::sin(angle);
	result.columns[2].data[2] = std::cos(angle);
	return result;
}

template<typename t_matrix>
inline t_matrix RotationMatrixZ(typename t_matrix::t_scalar angle) {
	t_matrix result;
	result.SetIdentity();
	result.columns[0].data[0] = std::cos(angle);
	result.columns[0].data[1] = std::sin(angle);
	result.columns[1].data[0] = -std::sin(angle);
	result.columns[1].data[1] = std::cos(angle);
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
inline t_matrix TranslationMatrix(typename t_matrix::t_scalar x,
								  typename t_matrix::t_scalar y,
								  typename t_matrix::t_scalar z) {
	typename t_matrix::t_vec translation = {x, y, z, t_matrix::t_scalar(1.0)};

	t_matrix result = result.SetIdentity();
	result.columns[3] = translation;
	return result;
}

template<typename t_matrix>
inline t_matrix ScaleMatrix(typename t_matrix::t_scalar x,
							typename t_matrix::t_scalar y,
							typename t_matrix::t_scalar z) {
	t_matrix result = result.SetIdentity();
	result.columns[0].data[0] = x;
	result.columns[1].data[1] = y;
	result.columns[2].data[2] = z;
	return result;
}

template<typename t_matrix>
inline t_matrix OrthographicProjectionMatrix(
		typename t_matrix::t_scalar m_left, typename t_matrix::t_scalar m_right,
		typename t_matrix::t_scalar m_bottom, typename t_matrix::t_scalar m_top,
		typename t_matrix::t_scalar m_near, typename t_matrix::t_scalar m_far) {
	t_matrix result = result.SetIdentity();
	result.columns[0].data[0] = 2 / (m_right - m_left);
	result.columns[1].data[1] = 2 / (m_top - m_bottom);
	result.columns[2].data[2] = -2 / (m_far - m_near);
	result.columns[3] = t_matrix::t_vec(
			{-((m_right + m_left) / (m_right - m_left)),
			 -((m_top + m_bottom) / (m_top - m_bottom)),
			 -((m_far + m_near) / (m_far - m_near)), t_matrix::t_scalar(1.0)});
	return result;
}

template<typename t_matrix>
inline t_matrix FrustrumProjectionMatrix(typename t_matrix::t_scalar fov,
										 typename t_matrix::t_scalar aspect,
										 typename t_matrix::t_scalar m_near,
										 typename t_matrix::t_scalar m_far) {
	t_matrix result = result.SetIdentity();
	result.columns[0] = t_matrix::t_vec(
			{(2 * m_near) / (aspect * std::tan(fov / 2)), t_matrix::t_scalar(0),
			 t_matrix::t_scalar(0), t_matrix::t_scalar(0)});
	result.columns[1] = t_matrix::t_vec(
			{t_matrix::t_scalar(0), (2 * m_near) / std::tan(fov / 2),
			 t_matrix::t_scalar(0), t_matrix::t_scalar(0)});
	result.columns[2] = t_matrix::t_vec(
			{t_matrix::t_scalar(0), t_matrix::t_scalar(0),
			 -(m_far + m_near) / (m_far - m_near), t_matrix::t_scalar(-1)});
	result.columns[3] = t_matrix::t_vec(
			{t_matrix::t_scalar(0), t_matrix::t_scalar(0),
			 -(2 * m_far * m_near) / (m_far - m_near), t_matrix::t_scalar(0)});
	return result;
}
}// namespace md_math

#endif// !MATRIX_LIBRARY_H
