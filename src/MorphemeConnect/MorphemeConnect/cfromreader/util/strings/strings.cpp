#pragma warning(disable : 4996)
#include "strings.h"

namespace cfr
{
	std::string   stringFromChar(char* c, int len)
	{
		int i;
		std::string s = "";
		
		for(i = 0; i < len; i++)
		{
			s = s + c[i];
		}

		return s;
	};

	std::wstring wstringFromWchar(wchar_t* c, int len)
	{
		std::wstring strArray(c);
		return strArray;
	};

	std::wstring wstringFromChar(char* c, int len)
	{
		std::string srcString;
		srcString.append((size_t)len,*c);
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring wide = converter.from_bytes(srcString);
		return wide;
	};

	std::string readString(MEM* src)
	{
		std::string str;
		char c = 'a';

		//mread(&c,sizeof(char),1,src);

		while((c != '\0') && (meod(src) == 0))
		{
			mread(&c,sizeof(char),1,src);
			str += c;
		}

		return str;
	};

	std::wstring readWstring(MEM* src)
	{
		std::wstring str;
		wchar_t c = 'a';

		//mread(&c,sizeof(char),1,src);

		while((c != '\0') && (meod(src) == 0))
		{
			mread(&c,sizeof(char),1,src);
			str += c;
		}

		return str;
	};

	std::wstring shortToWideString(std::string str)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		//std::string narrow = converter.to_bytes(wide_utf16_source_string);
		std::wstring wide = converter.from_bytes(str);

		return wide;
	};

	/*std::string readStringFromOffset(MEM* src)
	{
		long pos = mtell(src);
	};

	std::string readWStringFromOffset(MEM* src, bool unicode)
	{

	};*/

};