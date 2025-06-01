#include "Logger.h"

#define LOG_MODE_SETTING_NAME L"Log Mode"
#define LOG_FILE_NAME L"Scabture Log"

void Logger::init(bool debug)
{
	if (debug)
	{
		setMode(LogModeConsole);
	}
	else
	{
		LogMode mode = LogModeNone;
		SaveUtil::loadSettings(LOG_MODE_SETTING_NAME, &mode);
		setMode(mode);
	}
}

void Logger::saveMode(LogMode mode)
{
	SaveUtil::saveSettings(LOG_MODE_SETTING_NAME, &mode);
}

void Logger::logFormat(const wchar_t* format, va_list args)
{
	ExclusiveLockHolder holder(&_lock);
	if (_file == NULL)
	{
		return;
	}
	vfwprintf(_file, format, args);
	fflush(_file);
}

void Logger::logFormat(const wchar_t* format, ...)
{
	va_list args;
	va_start(args, format);
	logFormat(format, args);
	va_end(args);
}

void Logger::logMessage(const wchar_t* label, const wchar_t* format, va_list args)
{
	UniquePointer<const wchar_t> message = StringUtil::formatString(format, args);
	Date date = getDate();
	DWORD threadId = GetCurrentThreadId();
	logFormat(L"[%02i:%02i:%02i.%03i] Thread %u: %ls: %ls\n", date.hour, date.minute, date.second, date.millisecond, threadId, label, message);
}

void Logger::logMessage(const wchar_t* label, const wchar_t* format, ...)
{
	va_list args;
	va_start(args, format);
	logMessage(label, format, args);
	va_end(args);
}

Logger& Logger::getInstance()
{
	static Logger instance;
	return instance;
}

Logger::Logger()
{
	_file = NULL;
}

void Logger::setMode(LogMode mode)
{
	ExclusiveLockHolder holder(&_lock);
	if (_file != NULL && _file != stdout)
	{
		fclose(_file);
		_file = NULL;
	}
	switch (mode)
	{
		case LogModeNone:
		{
			_file = NULL;
			break;
		}
		case LogModeSingleFile:
		{
			UniquePointer<const wchar_t> path = StringUtil::formatString(L"%ls.txt", LOG_FILE_NAME);
			_file = _wfopen(path, L"w");
			break;
		}
		case LogModeNewFiles:
		{
			Date date = getDate();
			UniquePointer<const wchar_t> path = StringUtil::formatString(L"%ls %04i.%02i.%02i. %02i.%02i.%02i.%03i.txt", LOG_FILE_NAME, date.year, date.month, date.day, date.hour, date.minute, date.second, date.millisecond);
			_file = _wfopen(path, L"w");
			break;
		}
		case LogModeConsole:
		{
			_file = stdout;
			break;
		}
	}
}
