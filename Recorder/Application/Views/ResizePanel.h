#pragma once

class ResizePanel : public Panel
{
public:

	ResizePanel(Window* parent);

	void setWidth(int width);

	void setHeight(int height);

	void setResize(bool resize);

	void setKeepRatio(bool resize);

	void setEnabled(bool resize);

	int getWidth() const;

	int getHeight() const;
	
	bool getResize() const;

	bool getKeepRatio() const;

	const Event* getWidthChangeEvent() const;

	const Event* getHeightChangeEvent() const;

	const Event* getResizeChangeEvent() const;

	const Event* getKeepRatioChangeEvent() const;

private:

	UniquePointer<Label> _widthLabel;
	UniquePointer<Label> _heightLabel;
	UniquePointer<EditBox> _widthEdit;
	UniquePointer<EditBox> _heightEdit;
	UniquePointer<CheckBox> _resizeCheckbox;
	UniquePointer<CheckBox> _keepRatioCheckbox;
};
