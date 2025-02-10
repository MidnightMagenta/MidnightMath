#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MD_PI_DIGITS 3.14159265358979323
#define MD_E_DIGITS 2.71828182845904523

#define MD_DEFINE_CONSTANT(name, constant)                                     \
	constexpr float name##_f = constant;                                       \
	constexpr double name##_d = constant;

namespace md_math {
MD_DEFINE_CONSTANT(pi, MD_PI_DIGITS)
MD_DEFINE_CONSTANT(tau, MD_PI_DIGITS * 2.0)
MD_DEFINE_CONSTANT(e, MD_E_DIGITS)
}// namespace md_math

#endif// !CONSTANTS_H
