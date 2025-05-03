#pragma once

class WindowSelector : public SelectionWindow
{
public:

	WindowSelector(WindowArea area);

	bool hasSelectedWindow() const;

	HWND getSelectedWindow() const;

private:

	virtual void onMouseMove(int mouseX, int mouseY) override;

	virtual void onMouseClick(int mouseX, int mouseY) override;

	virtual void onKeyPress() override;

private:

	WindowArea _area;
	HWND _selectedWindow;
};

