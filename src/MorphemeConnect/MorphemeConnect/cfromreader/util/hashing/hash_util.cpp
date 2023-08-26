#include "hash_util.hpp"
#include "../files/files.hpp"

namespace cfr
{
	//opens file list for specific game and hashes on the fly for DVDBND support
	std::vector<std::string> getFileList(const char* path, GameHashList list)
	{
		std::vector<std::string> paths;

		switch(list)
		{
			case ds_ptde: break;
			default:
			{
				//TODO: fix this so it tells you what you input
				char* listChar;
				//char* thing = itoa((int)list,listChar,10);
				throw std::invalid_argument("getFileList Unsupported argument: \n");
			}
		}

		//open file and read to memory for performance
		FILE* listFile = v_fopen(path,"rb");

		if(listFile == NULL)
			throw std::runtime_error("Failed to open file list.\n");

		fseek(listFile,0,SEEK_END);
		int listFileSize = ftell(listFile);
		fseek(listFile,0,SEEK_SET);

		char* line;
		size_t lineSize = 128;
		size_t characters;

		line = (char*)malloc(lineSize * sizeof(char));

		while(feof(listFile) != 1 || ferror(listFile) != 0)
		{
			fgets(line,listFileSize,listFile);

			std::string filePath = line;

			if(filePath.back() == '\n')
				filePath.pop_back();

			paths.push_back(filePath);
		}

		fclose(listFile);

		return paths;
	}

	int32_t hashFilePath(std::string path)
	{
		int32_t hash = 0;

		for(int i = 0; i < path.size(); i++)
		{
			hash *= (int32_t)37;
			hash += (int32_t)path[i];
			//printf("h:%12.u 0x%12.x\n",hash,hash);
		}

		return hash;
	};

	//generates path key'd map of hashses for dvdbnd access.
	std::unordered_map<std::string, int32_t> createPathMap(std::vector<std::string> paths)
	{
		std::unordered_map<std::string, int32_t> hashTable;

		for(int i = 0; i < paths.size(); i++)
			hashTable.insert({paths[i],hashFilePath(paths[i].c_str())});

		return hashTable;
	};
};