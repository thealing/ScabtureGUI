#pragma once

class Logger : NonCopyable
{
public:

	static Logger& getInstance();

	void init(bool debug);

	void saveMode(LogMode mode);

	void logFormat(const wchar_t* format, va_list args);

	void logFormat(const wchar_t* format, ...);

	void logMessage(const wchar_t* label, const wchar_t* format, va_list args);

	void logMessage(const wchar_t* label, const wchar_t* format, ...);

private:

	Logger();

	void setMode(LogMode mode);

private:

	ExclusiveLock _lock;
	FILE* _file;
};
