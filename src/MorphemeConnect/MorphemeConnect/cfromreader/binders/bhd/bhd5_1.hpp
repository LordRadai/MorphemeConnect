#pragma once
#include "../stdafx.hpp"

namespace cfr
{
    class BHD5_1
    {
		public:
        struct Header
        {
            char magic[4]; // BHD5
            char unk04;
            char unk05;
            char unk06;
            char unk07;
            int32_t unk08; // 1
            int32_t fileSize;
            int32_t bucketCount;
            int32_t bucketsOffset; // 0x18
        };

        struct FileHeader
        {
            int32_t fileSize;
            int64_t offset;
        };

        struct Bucket
        {
            int32_t fileHeaderCount;
            int32_t fileHeadersOffset;
        };

        //FILE** headerSrc; //is this even needed?
		//char fileName[16]; //might need this to keep track of these
        //FILE* dataSrc;
		//hash key'd map of all file locations and sizes
		std::unordered_map<int32_t, FileHeader> hashMap;

        BHD5_1(FILE* headerSrc);
    };
};