#include "Editbox.h"

EditBox::EditBox(Window* parent)
{
	create(L"EDIT", NULL, WS_BORDER | ES_RIGHT | ES_NUMBER, parent);
	addCallback(editProc);
}

EditBox::~EditBox()
{
	removeCallback(editProc);
}

const Event* EditBox::getEditEvent() const
{
	return getChangeEvent();
}

LRESULT EditBox::editProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR subclassId, DWORD_PTR)
{
	EditBox* instance = (EditBox*)subclassId;
	if (instance != NULL)
	{
		if (message == WM_CHAR && wParam == VK_RETURN)
		{
			HWND parent = GetParent(window);
			SetFocus(parent);
			return 0;
		}
		if (message == WM_KILLFOCUS)
		{
			instance->onChange();
		}
	}
	return DefSubclassProc(window, message, wParam, lParam);
}
