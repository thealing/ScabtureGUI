#include "ControlUtil.h"

void ControlUtil::setText(Control* control, const wchar_t* format, ...)
{
	va_list args;
	va_start(args, format);
	setText(control, format, args);
	va_end(args);
}

void ControlUtil::setText(Control* control, const wchar_t* format, va_list args)
{
	UniquePointer<const wchar_t> text = StringUtil::formatString(format, args);
	control->setText(text);
}

void ControlUtil::setValue(Control* control, int value)
{
	setText(control, L"%i", value);
}

const wchar_t* ControlUtil::getText(const Control* control)
{
	int length = control->getTextLength();
	wchar_t* text = new wchar_t[length];
	control->getText(text, length);
	return text;
}

int ControlUtil::getValue(const Control* control)
{
	UniquePointer<const wchar_t> text = getText(control);
	int value = _wtoi(text);
	return value;
}
