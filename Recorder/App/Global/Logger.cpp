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
		SettingsProvider<LogMode> provider;
		LogMode mode;
		if (provider.load(LOG_MODE_SETTING_NAME, &mode))
		{
			wprintf(L"Loaded log mode %i.\n", mode);
			setMode(mode);
		}
		else
		{
			wprintf(L"No saved log mode found.\n");
		}
	}
}

void Logger::saveMode(LogMode mode)
{
	SettingsProvider<LogMode> provider;
	if (provider.save(LOG_MODE_SETTING_NAME, &mode))
	{
		wprintf(L"Saved log mode %i.\n", mode);
	}
	else
	{
		wprintf(L"Failed to save log mode %i.", mode);
	}
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
	int length = _vscwprintf(format, args) + 1;
	wchar_t* message = new wchar_t[length];
	vswprintf(message, length, format, args);
	Date date;
	getDate(&date);
	DWORD threadId = GetCurrentThreadId();
	logFormat(L"[%02i:%02i:%02i.%03i] Thread %u: %ls: %ls\n", date.hour, date.minute, date.second, date.millisecond, threadId, label, message);
	delete[] message;
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
			wchar_t fileName[MAX_PATH];
			swprintf(fileName, ARRAYSIZE(fileName), L"%ls.txt", LOG_FILE_NAME);
			_file = _wfopen(fileName, L"w");
			break;
		}
		case LogModeNewFiles:
		{
			Date date;
			getDate(&date);
			wchar_t fileName[MAX_PATH];
			swprintf(fileName, ARRAYSIZE(fileName), L"%ls [%04i.%02i.%02i.] [%02i.%02i.%02i.%03i].txt", LOG_FILE_NAME, date.year, date.month, date.day, date.hour, date.minute, date.second, date.millisecond);
			_file = _wfopen(fileName, L"w");
			break;
		}
		case LogModeConsole:
		{
			_file = stdout;
			break;
		}
	}
}
