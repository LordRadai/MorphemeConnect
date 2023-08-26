#pragma once
#include "../stdafx.hpp"

namespace cfr
{
	struct BND3
	{
		struct Header
		{
			char magic[4];
			char version[8];
			uint8_t rawFormat;
			uint8_t bigEndian;
			uint8_t bitBigEndian;
			char unk0F;
			int32_t fileCount;
			int32_t fileHeadersEnd;
			int32_t unk18;
			int32_t unk1C; //assert 0
		};

		struct File
		{
			//this part is always filled
			struct Header
			{
				char rawFlags;
				char unk01;
				char unk02;
				char unk03;

				int32_t compressedSize;
				uint32_t dataOffset;
			};

			Header* header;

			//circumstantially fill these
			int32_t id = 0;
			int32_t nameOffset = 0;
			int32_t uncompressedSize = 0;

			char** data;
		};

		Header* header;
		File* files;
	};

	//Init BND3 via current pos in memory
	BND3* openBND3(void* src, size_t size);

	//Init BND3 via a path
	BND3* openBND3(const char* path);

	//Init BND3 via a MEM pointer
	BND3* openBND3(MEM* mem);

	//Returns array of formats for a BND3
	//CfrFileType* getBnd3FileTypes(BND3* bnd);
};