#pragma once

class RectangleSelector : public SelectionWindow
{
public:

	RectangleSelector();

	bool hasSelectedRect() const;

	RECT getSelectedRect() const;

private:

	virtual void onMouseMove(int mouseX, int mouseY) override;

	virtual void onMouseClick(int mouseX, int mouseY) override;

	virtual void onKeyPress() override;

private:

	bool _clicked;
	int _startX;
	int _startY;
	RECT _selectedRect;
};

