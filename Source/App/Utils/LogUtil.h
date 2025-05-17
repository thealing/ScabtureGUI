#pragma once

class LogUtil
{
public:

	static void init(bool debug);

	static void saveMode(LogMode mode);

	static void logDebug(const wchar_t* format, va_list args);

	static void logDebug(const wchar_t* format, ...);

	static void logInfo(const wchar_t* format, va_list args);

	static void logInfo(const wchar_t* format, ...);

	static void logWarning(const wchar_t* format, va_list args);

	static void logWarning(const wchar_t* format, ...);

	static void logError(const wchar_t* format, va_list args);

	static void logError(const wchar_t* format, ...);

	static void logComWarning(const char* label, HRESULT result);

	static void logComError(const char* label, HRESULT result);

private:

	static bool isComResultSupressed(HRESULT result);
};

