#pragma once

class ComboBox : public Control
{
public:

	ComboBox(Window* parent);

	void setOptions(const wchar_t** options, int count);

	void setSelection(int selection);

	int getSelection() const;

	const Event* getSelectionEvent() const;

protected:

	virtual void onChange() override;

private:

	int _selection;

private:

	static LRESULT CALLBACK editProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR subclassId, DWORD_PTR data);
};

