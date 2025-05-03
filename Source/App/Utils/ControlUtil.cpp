#include "ControlUtil.h"

void ControlUtil::setText(Control* control, const wchar_t* format, ...)
{
	va_list args;
	va_start(args, format);
	int length = _vscwprintf(format, args);
	wchar_t* text = new wchar_t[length + 1];
	vswprintf(text, length + 1, format, args);
	va_end(args);
	control->setText(text);
	delete[] text;
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
	const wchar_t* text = getText(control);
	int value = _wtoi(text);
	delete text;
	return value;
}
