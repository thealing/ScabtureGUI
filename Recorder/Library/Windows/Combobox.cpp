#include "Combobox.h"

ComboBox::ComboBox(Window* parent)
{
	_selection = -1;
	create(L"COMBOBOX", NULL, CBS_AUTOHSCROLL | CBS_DROPDOWN | CBS_HASSTRINGS, parent);
	HWND listWindow = getHandle();
	HWND editWindow = FindWindowEx(listWindow, NULL, L"EDIT", NULL);
	if (editWindow != NULL)
	{
		SendMessage(editWindow, EM_SETREADONLY, TRUE, 0);
		SetWindowSubclass(editWindow, editProc, 0, 0);
	}
}

void ComboBox::setOptions(const wchar_t** options, int count)
{
	_selection = -1;
	sendMessage(CB_RESETCONTENT, 0, 0);
	for (int i = 0; i < count; i++)
	{
		_selection = 0; //debug
		sendMessage(CB_ADDSTRING, 0, (LPARAM)options[i]);
	}
}

void ComboBox::setSelection(int selection)
{
	_selection = selection;
	sendMessage(CB_SETCURSEL, (WPARAM)selection, 0);
}

int ComboBox::getSelection() const
{
	return _selection;
}

const Event* ComboBox::getSelectionEvent() const
{
	return getChangeEvent();
}

void ComboBox::onChange()
{
	_selection = (int)sendMessage(CB_GETCURSEL, 0, 0);
	Control::onChange();
}

LRESULT ComboBox::editProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR, DWORD_PTR)
{
	if (message == EM_SETSEL)
	{
		int start = (int)wParam;
		int end = (int)lParam;
		if (start != -1 && start != end)
		{
			return TRUE;
		}
	}
	if (message == WM_LBUTTONDOWN)
	{
		DefSubclassProc(window, message, wParam, lParam);
	}
	LRESULT result = DefSubclassProc(window, message, wParam, lParam);
	HideCaret(window);
	return result;
}
