#include "Debug.h"
#define DEBUG_LVL LVL_ERROR

void Debug::DebuggerMessage(MsgLevel level, const char* fmt, ...)
{
#ifdef _LOGGER
	va_list args;
	__va_start(&args, fmt);
	std::string msg_level;
	std::string msg_body;

	char msg[256];

	if (DEBUG_LVL < level)
		return;

	switch (level)
	{
	case LVL_DEBUG:
		msg_level = "[DEBUG]";
		break;
	case LVL_INFO:
		msg_level = "[INFO]";
		break;
	case LVL_WARN:
		msg_level = "[WARN]";
		break;
	case LVL_ERROR:
		msg_level = "[ERROR]";
		break;
	default:
		break;
	}

	msg_body = fmt;
	vsprintf_s(msg, (msg_level + " " + msg_body).c_str(), args);

#ifdef _CONSOLE
	printf_s(msg);
#endif

	OutputDebugStringA(msg);
#endif
}

void Debug::Panic(const char* src_module, const char* fmt, ...)
{
	va_list args;
	__va_start(&args, fmt);

	char msg[256];

	vsprintf_s(msg, fmt, args);

	try
	{
		throw std::exception(msg);
	}
	catch (std::exception)
	{
		ShowCursor(true);
		MessageBoxA(NULL, msg, src_module, MB_ICONERROR);
	}

	abort();
}

void Debug::Alert(MsgLevel level, const char* src_module, const char* fmt, ...)
{
	va_list args;
	__va_start(&args, fmt);

	char msg[256];
	UINT type = MB_ICONASTERISK;

	vsprintf_s(msg, fmt, args);

	Debug::DebuggerMessage(level, fmt, args);

	switch (level)
	{
	case Debug::LVL_DEBUG:
		type = MB_ICONINFORMATION;
		break;
	case Debug::LVL_INFO:
		type = MB_ICONINFORMATION;
		break;
	case Debug::LVL_WARN:
		type = MB_ICONEXCLAMATION;
		break;
	case Debug::LVL_ERROR:
		type = MB_ICONERROR;
		break;
	default:
		Panic("Debug.cpp", "Invalid debug level\n");
		return;
	}

	ShowCursor(true);
	MessageBoxA(NULL, msg, "MorphemeConnect", type);
}