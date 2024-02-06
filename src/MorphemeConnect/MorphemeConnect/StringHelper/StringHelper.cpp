#include <filesystem>
#include "StringHelper.h"

std::string StringHelper::ToNarrow(const wchar_t* s, char dfault,
	const std::locale& loc)
{
	std::ostringstream stm;

	while (*s != L'\0') {
		stm << std::use_facet< std::ctype<wchar_t> >(loc).narrow(*s++, dfault);
	}
	return stm.str();
}

std::string StringHelper::FloatToString(float value, int precision)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(precision) << value;
	return ss.str();
}

std::wstring StringHelper::ToWide(const std::string& s)
{
	return std::wstring(s.begin(), s.end());
}

std::string StringHelper::RemoveExtension(std::string filename)
{
	size_t lastdot = filename.find_last_of(".");

	if (lastdot == std::string::npos) return filename;

	return filename.substr(0, lastdot);
}