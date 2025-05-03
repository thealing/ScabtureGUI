#include "Button.h"

Button::Button(Window* parent, const wchar_t* text)
{
	create(L"BUTTON", text, BS_PUSHBUTTON, parent);
}

const Event* Button::getClickEvent() const
{
    return getChangeEvent();
}
