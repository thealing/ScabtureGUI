#pragma once

class WindowSelector : public SelectionWindow
{
public:

	WindowSelector();

	HWND getSelectedWindow() const;

private:

	HWND getWindowUnderPoint(POINT point);

private:

	virtual void onMouseMove(int mouseX, int mouseY) override;

	virtual void onMouseClick(int mouseX, int mouseY) override;

	virtual void onKeyPress() override;

private:

	HWND _selectedWindow;
};

