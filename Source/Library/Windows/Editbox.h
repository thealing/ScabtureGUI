#pragma once

class EditBox : public Control
{
public:

	EditBox(Window* parent);

	~EditBox();

	const Event* getEditEvent() const;

private:

	static LRESULT CALLBACK editProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR subclassId, DWORD_PTR data);
};

