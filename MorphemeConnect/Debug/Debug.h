#pragma once
#include <windows.h>
#include <string>
#include <debugapi.h>

namespace Debug
{
	enum MsgLevel
	{
		LVL_DEBUG = 200000001,
		LVL_INFO = 1000000001,
		LVL_WARN = 1300000001,
		LVL_ERROR = 1400000001,
	};

	void DebuggerMessage(MsgLevel level, const char* fmt, ...);
	void Panic(const char* src_module, const char* fmt, ...);
	void Alert(UINT type, const char* src_module, const char* fmt, ...);
}