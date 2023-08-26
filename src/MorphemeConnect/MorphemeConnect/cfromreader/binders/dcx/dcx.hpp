#pragma once
#include "../stdafx.hpp"

namespace cfr
{
	//i'm 99% sure this code is somewhere else as well. can't find it.
	enum _DCX_TYPE_
	{
		unkown,
		none,
		zlib,
		dcp_edge,
		dcp_dflt,
		dcx_edge,
		dcx_dflt_10000_24_9,
		dcx_dflt_10000_44_9,
		dcx_dflt_11000_44_8,
		dcx_dflt_11000_44_9,
		dcx_krak
	};

	int decompress_zlib(FILE* src, MEM* dest);

	int decompress_dcp_edge(MEM* dest);

	int decompress_dcp_dflt(FILE* src, MEM* dest);

	int decompress_dcx_edge(MEM* dest, _DCX_TYPE_ type);

	int decompress_dcx_dflt(FILE* src, MEM* dest, _DCX_TYPE_ type);

	int decompress_dcx_krak(MEM* dest);
	
	//char* setupDCX(FILE* data, size_t* size);

	//Returns a char* array of a decompressed DCX file.
	//src: FILE* to the DCX
	//size: is set to the size of the array
	char* openDCX(MEM* src, size_t* size);

	//Returns a char* array of a decompressed DCX file.
	//path: const char* file path of the DCX
	//size: is set to the size of the array
	char* openDCX(const char* path, size_t* size);

	//Returns a char* array of a decompressed DCX file.
	//pulls a known size DCX, and blah blah blah
	char* openDCX(FILE* file, size_t compressedSize, size_t* uncompressedSize);
};