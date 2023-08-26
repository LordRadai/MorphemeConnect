#pragma once

//#include "../memr/memr.hpp"
#include "../../cmem.h"
#include <assert.h>
#include <stdio.h>
#include <zlib.h>

#ifndef ZLIB_INF__
#define ZLIB_INF__

//TODO: is this needed?
#ifdef _WIN32
#include "io.h"
#endif

#ifndef CHUNK
#	define CHUNK 16384
#endif

namespace cfr
{
	int inf(FILE *source, MEM *dest);
};

#endif