#pragma once
#include <ostream>
#include <string>
#include <sstream>
#include <iomanip>

namespace StringHelper
{
	std::string ToNarrow(const wchar_t* s, char dfault = '?', const std::locale& loc = std::locale());
	std::string FloatToString(float value, int precision = 3);
	std::wstring ToWide(const std::string& s);
	std::string RemoveExtension(std::string filename);
	std::string Replace(std::string str, std::string substr, std::string replacement);
}