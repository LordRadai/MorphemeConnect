#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

namespace cfr
{
	//fopen() with extra validation and auto abort.
#ifdef _WIN32
	FILE* v_fopen(const char* filename, const char* modes);
#else
	FILE* v_fopen(const char* __restrict__ __filename, const char* __restrict__ __modes);
#endif
};