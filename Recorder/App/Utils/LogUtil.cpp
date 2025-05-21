#include "LogUtil.h"

void LogUtil::init(bool debug)
{
	Logger& logger = Logger::getInstance();
	logger.init(debug);
}

void LogUtil::saveMode(LogMode mode)
{
	Logger& logger = Logger::getInstance();
	logger.saveMode(mode);
}

void LogUtil::logDebug(const wchar_t* format, va_list args)
{
	Logger& logger = Logger::getInstance();
	logger.logMessage(L"Debug", format, args);
}

void LogUtil::logDebug(const wchar_t* format, ...)
{
	va_list args;
	va_start(args, format);
	logDebug(format, args);
	va_end(args);
}

void LogUtil::logInfo(const wchar_t* format, va_list args)
{
	Logger& logger = Logger::getInstance();
	logger.logMessage(L"Info", format, args);
}

void LogUtil::logInfo(const wchar_t* format, ...)
{
	va_list args;
	va_start(args, format);
	logInfo(format, args);
	va_end(args);
}

void LogUtil::logWarning(const wchar_t* format, va_list args)
{
	Logger& logger = Logger::getInstance();
	logger.logMessage(L"Warning", format, args);
}

void LogUtil::logWarning(const wchar_t* format, ...)
{
	va_list args;
	va_start(args, format);
	logWarning(format, args);
	va_end(args);
}

void LogUtil::logError(const wchar_t* format, va_list args)
{
	Logger& logger = Logger::getInstance();
	logger.logMessage(L"Error", format, args);
}

void LogUtil::logError(const wchar_t* format, ...)
{
	va_list args;
	va_start(args, format);
	logError(format, args);
	va_end(args);
}

void LogUtil::logComWarning(const char* label, HRESULT result)
{
	if (isComResultSupressed(result))
	{
		return;
	}
	logWarning(L"%hs: Failed with error 0x%08X.", label, result);
}

void LogUtil::logComError(const char* label, HRESULT result)
{
	if (isComResultSupressed(result))
	{
		return;
	}
	logError(L"%hs: Failed with error 0x%08X.", label, result);
}

bool LogUtil::isComResultSupressed(HRESULT result)
{
	if (result == E_ILLEGAL_METHOD_CALL)
	{
		return true;
	}
	if (result == MF_E_TRANSFORM_INPUT_REMAINING)
	{
		return true;
	}
	if (result == MF_E_TRANSFORM_NEED_MORE_INPUT)
	{
		return true;
	}
    return false;
}
