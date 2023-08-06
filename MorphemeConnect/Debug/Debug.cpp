#include "Debug.h"

void Debug::DebuggerMessage(MsgLevel level, const char* fmt, ...)
{
#ifdef _LOGGER
	va_list args;
	__va_start(&args, fmt);
	std::string msg_level;
	std::string msg_body;

	char msg[256];

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

	printf_s(msg);
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