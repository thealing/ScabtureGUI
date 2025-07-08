#pragma once

class StringUtil
{
public:

	static const wchar_t* formatString(const wchar_t* format, va_list args);

	static const wchar_t* formatString(const wchar_t* format, ...);
};

