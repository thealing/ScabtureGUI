#include "QualityPanel.h"

QualityPanel::QualityPanel(Window* parent) : Panel(parent)
{
	setBounds(Rect(610, 0, 790, 65));
	_frameRateLabel = new Label(this, L"Frame Rate (FPS):");
	_frameRateLabel->setBounds(Vector(12, 10), Vector(100, 20));
	_bitRateLabel = new Label(this, L"Bit Rate (KBPS):");
	_bitRateLabel->setBounds(Vector(12, 35), Vector(100, 20));
	_frameRateEdit = new EditBox(this);
	_frameRateEdit->setBounds(Vector(120, 10), Vector(50, 20));
	_bitRateEdit = new EditBox(this);
	_bitRateEdit->setBounds(Vector(120, 35), Vector(50, 20));
	FontStore& fontStore = FontStore::getInstance();
	setChildrenFont(fontStore.getPanelFont());
}

void QualityPanel::setFrameRate(int frameRate)
{
	ControlUtil::setValue(_frameRateEdit, frameRate);
}

void QualityPanel::setBitRate(int bitRate)
{
	ControlUtil::setValue(_bitRateEdit, bitRate);
}

int QualityPanel::getFrameRate() const
{
	return ControlUtil::getValue(_frameRateEdit);
}

int QualityPanel::getBitRate() const
{
	return ControlUtil::getValue(_bitRateEdit);
}

const Event* QualityPanel::getFrameRateChangeEvent() const
{
	return _frameRateEdit->getChangeEvent();
}

const Event* QualityPanel::getBitRateChangeEvent() const
{
	return _bitRateEdit->getChangeEvent();
}
