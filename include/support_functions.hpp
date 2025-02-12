#ifndef SUPPORT_FUNCTIONS_H
#define SUPPORT_FUNCTIONS_H

#include <intrin.h>

namespace md_math::support {
bool CheckSIMD_Support() {
	int cpuInfo[4];
	__cpuid(cpuInfo, 1);
	if (!(cpuInfo[2] & (1 << 28))) { return false; }
	__cpuid(cpuInfo, 7);
	if (!(cpuInfo[1] & (1 << 5))) { return false; }
	return true;
}
}// namespace md_math::support

#endif// !SUPPORT_FUNCTIONS_H
