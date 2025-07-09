#include "DialogUtil.h"

Control* DialogUtil::createLabel(Window* parent, const wchar_t* text, int x, int y, int width, int height)
{
	Control* control = new Label(parent, text);
	control->setBounds(x, y, width, height);
	return control;
}

Control* DialogUtil::createButton(Window* parent, const wchar_t* text, int x, int y, int width, int height)
{
	Control* control = new Button(parent, text);
	control->setBounds(x, y, width, height);
	return control;
}

Control* DialogUtil::createCheckBox(Window* parent, bool* value, int x, int y, int width, int height)
{
	Control* control = new DataCheckBox(parent, value);
	control->setBounds(x, y, width, height);
	return control;
}

Control* DialogUtil::createComboBox(Window* parent, int* value, const wchar_t** options, int count, int x, int y, int width, int height)
{
	Control* control = new DataComboBox(parent, value, options, count);
	control->setBounds(x, y, width, height + height * count);
	return control;
}

Control* DialogUtil::createHotkeyEdit(Window* parent, Hotkey* value, int x, int y, int width, int height)
{
	Control* control = new HotkeyEdit(parent, value);
	control->setBounds(x, y, width, height);
	return control;
}

Control* DialogUtil::createSeparator(Window* parent, int x, int y, int width, int height)
{
	Control* control = new Separator(parent);
	control->setBounds(x, y, width, height);
	return control;
}
