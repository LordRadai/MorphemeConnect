#include "compat.hpp"

namespace cfr
{
	unsigned int reverse(unsigned int x)
	{
		x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
		x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
		x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
		x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
		return((x >> 16) | (x << 16));
	}

	unsigned int bitswap(unsigned int i)
	{
#ifdef _GNU
		return __builtin_bswap32(i);
#else
		return reverse(i);
#endif
	};

/*	size_t getline2(char** lineptr, size_t* n, FILE* stream)
	{
#ifdef _GNU
		return getline(lineptr,n,stream);
#else
		int i = 0;

		while(feof(stream))
		{

		}
#endif
	};*/
};