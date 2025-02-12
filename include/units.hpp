#ifndef UNITS_H
#define UNITS_H

#define MD_MATH_DEFINE_UNIT(name, value)                                       \
	constexpr float name##_f = value;                                          \
	constexpr double name##_d = value;

namespace md_math::units {
//distance
MD_MATH_DEFINE_UNIT(pm, 1e+9)
MD_MATH_DEFINE_UNIT(um, 1e+6)
MD_MATH_DEFINE_UNIT(mm, 1e+3)
MD_MATH_DEFINE_UNIT(cm, 1e+2)
MD_MATH_DEFINE_UNIT(m, 1)
MD_MATH_DEFINE_UNIT(km, 1e-3)
MD_MATH_DEFINE_UNIT(inch, 39.37007874)
MD_MATH_DEFINE_UNIT(foot, 3.280839895)
MD_MATH_DEFINE_UNIT(yard, 1.0936132983)
MD_MATH_DEFINE_UNIT(mile, 0.0006213712)

//mass
MD_MATH_DEFINE_UNIT(pg, 1e+9)
MD_MATH_DEFINE_UNIT(ug, 1e+6)
MD_MATH_DEFINE_UNIT(mg, 1e+3)
MD_MATH_DEFINE_UNIT(g, 1)
MD_MATH_DEFINE_UNIT(kg, 1e-3)
MD_MATH_DEFINE_UNIT(ton, 1e-6)
MD_MATH_DEFINE_UNIT(lb, 0.0022046226)

//time
MD_MATH_DEFINE_UNIT(ps, 1e+9)
MD_MATH_DEFINE_UNIT(us, 1e+6)
MD_MATH_DEFINE_UNIT(ms, 1e+3)
MD_MATH_DEFINE_UNIT(sec, 1);
MD_MATH_DEFINE_UNIT(minute, 1 / 60)
MD_MATH_DEFINE_UNIT(hour, 1 / 3600)
MD_MATH_DEFINE_UNIT(day, 86400)

//current
MD_MATH_DEFINE_UNIT(pA, 1e+9)
MD_MATH_DEFINE_UNIT(uA, 1e+6)
MD_MATH_DEFINE_UNIT(mA, 1e+3)
MD_MATH_DEFINE_UNIT(A, 1)
MD_MATH_DEFINE_UNIT(kA, 1e-3)
MD_MATH_DEFINE_UNIT(MA, 1e-6)
MD_MATH_DEFINE_UNIT(GA, 1e-9)

//temperature
inline float CelciusToFarenheit(float celcius) {
	return (celcius * (9 / 5)) + 32;
}
inline double CelciusToFarenheit(double celcius) {
	return (celcius * (9 / 5)) + 32;
}
inline float FarenheitToCelcius(float farenheit) {
	return (farenheit - 32) * (5 / 9);
}
inline double FarenheitToCelcius(double farenheit) {
	return (farenheit - 32) * (5 / 9);
}
inline float CelciusToKelvin(float celcius) { return celcius + 273.15; }
inline double CelciusToKelvin(double celcius) { return celcius + 273.15; }
inline float KelvinToCelcius(float kelvin) { return kelvin - 273.15; }
inline double KelvinToCelcius(double kelvin) { return kelvin - 273.15; }

//ammount of substance
MD_MATH_DEFINE_UNIT(mole, 1);

//luminesance
MD_MATH_DEFINE_UNIT(cd, 1)
}// namespace md_math::units

#endif// !UNITS_H
