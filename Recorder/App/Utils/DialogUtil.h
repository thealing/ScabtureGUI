#pragma once

class DialogUtil
{
public:

	static const wchar_t* getTitle(Window* window);

	static Control* createLabel(Window* parent, const wchar_t* text, int x, int y, int width, int height);

	static Control* createButton(Window* parent, const wchar_t* text, int x, int y, int width, int height);

	static Control* createCheckBox(Window* parent, bool* value, int x, int y, int width, int height);

	static Control* createComboBox(Window* parent, int* value, const wchar_t** options, int count, int x, int y, int width, int height);

	static Control* createHotkeyEdit(Window* parent, Hotkey* value, int x, int y, int width, int height);

	static Control* createSeparator(Window* parent, int x, int y, int width, int height);
};

