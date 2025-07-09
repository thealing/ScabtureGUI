#pragma once

class HotkeyEdit : public Control
{
public:

	HotkeyEdit(Window* parent, Hotkey* value);

	~HotkeyEdit();

private:

	void update();

private:

	Hotkey* _value;

private:

	static LRESULT CALLBACK hotkeyProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR subclassId, DWORD_PTR data);
};

