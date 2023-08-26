#pragma once
#include "../stdafx.hpp"
#include "../../cmem.h"

namespace cfr
{
	std::string   stringFromChar(char* c, int len);
	std::wstring wstringFromWchar(wchar_t* c, int len);
	std::wstring wstringFromChar(char* c, int len);

	std::string readString(MEM* src);

	std::wstring readWstring(MEM* src);

	std::wstring shortToWideString(std::string str);

	//goto offset, then generate string from null term'd chars.
	//std::string readStringFromOffset(MEM* src);

	//goto offset, then generate string from null term'd chars. bool true if source are wchars.
	//std::string readWStringFromOffset(MEM* src, bool unicode);
};