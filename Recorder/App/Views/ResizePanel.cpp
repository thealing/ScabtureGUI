#include "ResizePanel.h"

ResizePanel::ResizePanel(Window* parent) : Panel(parent)
{
	setBounds(Rect(370, 0, 615, 65));
	_widthLabel = new Label(this, L"Width: ");
	_widthLabel->setBounds(Vector(12, 10), Vector(50, 20));
	_heightLabel = new Label(this, L"Height: ");
	_heightLabel->setBounds(Vector(12, 35), Vector(50, 20));
	_widthEdit = new EditBox(this);
	_widthEdit->setBounds(Vector(70, 10), Vector(50, 20));
	_heightEdit = new EditBox(this);
	_heightEdit->setBounds(Vector(70, 35), Vector(50, 20));
	_resizeCheckbox = new CheckBox(this, L"Resize");
	_resizeCheckbox->setBounds(Vector(150, 10), Vector(75, 20));
	_keepRatioCheckbox = new CheckBox(this, L"Keep Ratio");
	_keepRatioCheckbox->setBounds(Vector(150, 35), Vector(75, 20));
	FontStore& fontStore = FontStore::getInstance();
	setChildrenFont(fontStore.getPanelFont());
}

void ResizePanel::setWidth(int width)
{
	ControlUtil::setValue(_widthEdit, width);
}

void ResizePanel::setHeight(int height)
{
	ControlUtil::setValue(_heightEdit, height);
}

void ResizePanel::setResize(bool resize)
{
	_resizeCheckbox->setChecked(resize);
}

void ResizePanel::setKeepRatio(bool resize)
{
	_keepRatioCheckbox->setChecked(resize);
}

void ResizePanel::setEnabled(bool resize)
{
	_widthEdit->setEnabled(resize);
	_heightEdit->setEnabled(resize);
}

int ResizePanel::getWidth() const
{
    return ControlUtil::getValue(_widthEdit);
}

int ResizePanel::getHeight() const
{
	return ControlUtil::getValue(_heightEdit);
}

bool ResizePanel::getResize() const
{
	return _resizeCheckbox->getChecked();
}

bool ResizePanel::getKeepRatio() const
{
	return _keepRatioCheckbox->getChecked();
}

const Event* ResizePanel::getWidthChangeEvent() const
{
    return _widthEdit->getEditEvent();
}

const Event* ResizePanel::getHeightChangeEvent() const
{
    return _heightEdit->getEditEvent();
}

const Event* ResizePanel::getResizeChangeEvent() const
{
    return _resizeCheckbox->getCheckEvent();
}

const Event* ResizePanel::getKeepRatioChangeEvent() const
{
    return _keepRatioCheckbox->getCheckEvent();
}
