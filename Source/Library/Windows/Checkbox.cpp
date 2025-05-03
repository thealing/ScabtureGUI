#include "Checkbox.h"

CheckBox::CheckBox(Window* parent, const wchar_t* text)
{
	create(L"BUTTON", text, BS_AUTOCHECKBOX | BS_CHECKBOX, parent);
}

void CheckBox::setChecked(bool checked)
{
	int state = checked ? BST_CHECKED : BST_UNCHECKED;
	sendMessage(BM_SETCHECK, state, 0);
}

bool CheckBox::getChecked()
{
	int state = (int)sendMessage(BM_GETCHECK, 0, 0);
	return state == BST_CHECKED;
}

const Event* CheckBox::getCheckEvent() const
{
	return getChangeEvent();
}
