#pragma once

class ControlUtil
{
public:

	static void setText(Control* control, const wchar_t* format, ...);

	static void setText(Control* control, const wchar_t* format, va_list args);

	static void setValue(Control* control, int value);

	static const wchar_t* getText(const Control* control);

	static int getValue(const Control* control);
};

