#include "StringUtil.h"

const wchar_t* StringUtil::formatString(const wchar_t* format, va_list args)
{
	int length = _vscwprintf(format, args) + 1;
	wchar_t* string = new wchar_t[length];
	vswprintf(string, length, format, args);
	return string;
}

const wchar_t* StringUtil::formatString(const wchar_t* format, ...)
{
	va_list args;
	va_start(args, format);
	const wchar_t* string = formatString(format, args);
	va_end(args);
	return string;
}
