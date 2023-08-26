#include "bnd3.hpp"

namespace cfr
{
	BND3* initBND3(MEM* src)
	{
		BND3* bnd = (BND3*)malloc(sizeof(BND3));

		bnd->header = (BND3::Header*)mtellptr(src);
		mseek(src,sizeof(BND3::Header),SEEK_CUR);

		for(int i = 0; i < 4; i++)
			printf("%c",bnd->header->magic[i]);
		printf("\n");

		bnd->files = (BND3::File*)malloc(sizeof(BND3::File)*bnd->header->fileCount);

		for(int i = 0; i < bnd->header->fileCount; i++)
		{
			bnd->files[i].header = (BND3::File::Header*)mtellptr(src);
			mseek(src,sizeof(BND3::File::Header),SEEK_CUR);

			if(bnd->header->rawFormat & 0b01000000)
				mread(&bnd->files[i].id,sizeof(int32_t),1,src);

			if((bnd->header->rawFormat & 0b00100000) | (bnd->header->rawFormat & 0b00010000))
				mread(&bnd->files[i].nameOffset,sizeof(int32_t),1,src);

			if(bnd->header->rawFormat & 0b00000100)
				mread(&bnd->files[i].uncompressedSize,sizeof(int32_t),1,src);

			//bnd->files[i].data = (char**)mtellptr(src) + mtell(src);
			bnd->files[i].data = (char**)(bnd->files[i].header->dataOffset+src->src);

			//don't seek the memory isn't here!
			//mseek(src,*bnd->files[i].uncompressedSize,SEEK_CUR);
		}

		return bnd;
	};

	BND3* openBND3(void* src, size_t size)
	{
		MEM* mem = mopen((char*)src,size);
		BND3* bnd = initBND3(mem);
		mclose(mem);
		return bnd;
	};

	BND3* openBND3(const char* path)
	{
		//load entire file into memory
		FILE* fp = v_fopen(path,"br");
		fseek(fp,0,SEEK_END);
		int size = ftell(fp);
		fseek(fp,0,SEEK_SET);
		char* data = (char*)malloc(size);
		fread(&data[0],size,1,fp);
		fclose(fp);

		return openBND3(data,size);
	};

	BND3* openBND3(MEM* mem)
	{
		return initBND3(mem);
	};
};