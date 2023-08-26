#ifndef CFR_HASH_UTIL__
#define CFR_HASH_UTIL__

#pragma once

//#include "../compat/compat.hpp"
#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

//#include "ds_ptde.hpp"

; //i have no idea why this is needed

namespace cfr
{
	enum GameHashList
	{
		des,
		ds_ptde,
		ds_r, //doesn't need it, unpacked by default
		ds_2,
		ds_2_sotfs,
		ds_3,
		bb,
		sek,
		er
	};
	
	//opens file list for specific game and hashes on the fly for DVDBND support
	std::vector<std::string> getFileList(const char* path, GameHashList list);

	int32_t hashFilePath(std::string path);

	//generates path key'd map of hashses for dvdbnd access.
	std::unordered_map<std::string, int32_t> createPathMap(std::vector<std::string> paths);
};

#endif