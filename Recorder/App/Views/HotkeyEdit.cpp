#include "HotkeyEdit.h"

HotkeyEdit::HotkeyEdit(Window* parent, Hotkey* value) : _value(value)
{
	create(L"EDIT", NULL, WS_BORDER | ES_RIGHT, parent);
	addCallback(hotkeyProc);
	update();
}

HotkeyEdit::~HotkeyEdit()
{
	removeCallback(hotkeyProc);
}

void HotkeyEdit::update()
{
	wchar_t text[32] = {};
	if (_value->control)
	{
		wcscat(text, L"Ctrl+");
	}
	if (_value->shift)
	{
		wcscat(text, L"Shift+");
	}
	if (_value->alt)
	{
		wcscat(text, L"Alt+");
	}
	if (_value->key == 0)
	{
		wcscpy(text, L"None");
	}
	else
	{
		size_t length = wcslen(text);
		text[length] = _value->key;
	}
	setText(text);
}

LRESULT HotkeyEdit::hotkeyProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR subclassId, DWORD_PTR)
{
	HotkeyEdit* instance = (HotkeyEdit*)subclassId;
	if (instance != NULL)
	{
		if (message == WM_KEYDOWN)
		{
			wchar_t key = (wchar_t)wParam;
			if (iswalnum(key))
			{
				instance->_value->key = key;
				instance->_value->shift = GetKeyState(VK_SHIFT) & 0x8000;
				instance->_value->control = GetKeyState(VK_CONTROL) & 0x8000;
				instance->_value->alt = GetKeyState(VK_MENU) & 0x8000;
			}
			if (key == VK_BACK || key == VK_DELETE)
			{
				instance->_value->key = 0;
			}
			instance->update();
		}
	}
	if (message == WM_CHAR || message == WM_KEYDOWN)
	{
		return 0;
	}
	return DefSubclassProc(window, message, wParam, lParam);
}
