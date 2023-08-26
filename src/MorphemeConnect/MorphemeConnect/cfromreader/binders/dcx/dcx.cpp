#include "dcx.hpp"

namespace cfr
{
	/*char* openDCX(const char* path, size_t* size)
	{
		FILE* dcx = v_fopen(path,"rb");
		
		//load entire file into memory
		fseek(dcx,0,SEEK_END);
		size_t fileSize = ftell(dcx);
		char* dcxMem = (char*)malloc(fileSize*sizeof(char));
		fseek(dcx,0,SEEK_SET);
		fread(dcxMem,fileSize,1,dcx);
		fclose(dcx);

		mopen(dcxMem,fileSize);

		return openDCX(dcxMem,size);
	};*/

	char* openDCX(FILE* src, size_t compressedSize, size_t* uncompressedSizeOut)
	{
		char magic[4];

		fread(magic,4,1,src);
		if(memcmp(magic,"DCX\0",4) != 0){return NULL;}

		int32_t unk04;
		fread(&unk04,4,1,src);
		unk04 = bitswap(unk04);

		fseek(src,8,SEEK_CUR);

		int32_t unk10;
		fread(&unk10,4,1,src);
		unk10 = bitswap(unk10);

		fseek(src,8,SEEK_CUR);

		uint32_t uncompressedSize = 0;
		fread(&uncompressedSize,4,1,src);
		uncompressedSize = bitswap(uncompressedSize);

		fseek(src,8,SEEK_CUR);

		char format[4];
		fread(format,4,1,src); //format

		fseek(src,4,SEEK_CUR);

		int8_t unk30;
		fread(&unk30,1,1,src);
		unk30 = bitswap(unk30);

		fseek(src,23,SEEK_CUR); //race to end
		if(memcmp(format,"EDGE",4) == 0)
		{
			//do edge stuff
			//seek thru edge
		}

		//alloc and set up the output buffer
		char* buff = (char*)malloc(uncompressedSize);
		*uncompressedSizeOut = (uncompressedSize);
		MEM* dest = mopen(buff,uncompressedSize);

		//call correct decompression util and copy output into dest
		_DCX_TYPE_ type;

		if(memcmp(magic,"DCP\0",4) == 0)
		{
			printf("DCP\n");
			if(memcmp(format,"DFLT",4) == 0)
			{
				type = dcp_dflt;
				decompress_dcp_dflt(src,dest);
			}
			else if(memcmp(format,"EDGE",4) == 0)
			{
				type = dcp_edge;
			}
			throw std::runtime_error("No DCP compression method format found!\n");
		}
		else if(memcmp(magic,"DCX",3) == 0)
		{
			//printf("DCX\n");
			if(memcmp(format,"DFLT",4) == 0)
			{
				if(unk10 == 0x24)
				{
					type = dcx_dflt_10000_24_9;
					decompress_dcx_dflt(src,dest,type);
				}
				else if(unk10 == 0x44)
				{
					if(unk04 == 0x10000)
					{
						type = dcx_dflt_10000_44_9;
						decompress_dcx_dflt(src,dest,type);
					}
					else if(unk04 == 0x11000)
					{
						if(unk30 == 0x8000000)
						{
							type = dcx_dflt_11000_44_8;
							decompress_dcx_dflt(src,dest,type);
						}
						else if(unk30 == 0x9000000)
						{
							type = dcx_dflt_11000_44_9;
							decompress_dcx_dflt(src,dest,type);
						}
					}
				}
				else
				{
					printf("unk04:%i\n",unk04);
					printf("unk10:%i\n",unk10);
					printf("unk30:%i\n",unk30);
					throw std::runtime_error("Failed to parse DCX format!\n");
				}
				//decompress_dcx_edge(file,type);
			}
			else if(memcmp(format,"EDGE",4) == 0)
			{
				type = dcx_edge;
				//decompress_dcx_edge(data,dest);
			}
			else if(memcmp(format,"KRAK",4) == 0)
			{
				//decompress_dcx_krak(file);
			}
		}
		else
		{
			printf("Using standard ZLIB!\n");
			decompress_zlib(src,dest);
		}

		//clean up!!!
		fclose(src);
		mclose(dest);
		return buff;
	};

	int decompress_zlib(FILE* src, MEM* dest)
	{
		//call inflate_zlib
		
		return inf(src,dest);
	};

	int decompress_dcp_edge(MEM* dest)
	{
		return 0;
	};

	int decompress_dcp_dflt(FILE* src, MEM* dest)
	{
		printf("current location:%x\n",ftell(src));
		//call inflate_zlib
		return 0;
	};

	int decompress_dcx_edge(MEM* dest, _DCX_TYPE_ type)
	{
		//similar to inflate_zlib.. but not quite.
		return 0;
	};

	int decompress_dcx_dflt(FILE* src, MEM* dest, _DCX_TYPE_ type)
	{
		fseek(src,4,SEEK_CUR); //skip to beginning of dlft data
		int ret = inf(src,dest);

		if(ferror(src))
			throw std::runtime_error("Source file errored during inflation!\n");

		if(ret != 0)
		{
			printf("inflate ret: %i\n", ret);
			throw std::runtime_error("Failed to inflate DCX DFLT file!\n");
		}

		return 0;
	};

	int decompress_dcx_krak(MEM* dest)
	{
		return 0;
	};
};