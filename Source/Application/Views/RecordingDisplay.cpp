#include "RecordingDisplay.h"

RecordingDisplay::RecordingDisplay(Window* parent) : Frame(parent)
{
	setAnchor(AnchorBottomLeft);
	setBounds(Vector(210, 0), Vector(190, 80));
	_timeLabel = new Label(this, L"", Label::AlignRight);
	_timeLabel->setBounds(Vector(15, 10), Vector(155, 30));
	_sizeLabel = new Label(this, L"", Label::AlignRight);
	_sizeLabel->setBounds(Vector(10, 40), Vector(160, 30));
	FontStore& fontStore = FontStore::getInstance();
	setChildrenFont(fontStore.getDisplayFont());
	setRecordingTime(0);
	setRecordingSize(0);
}

void RecordingDisplay::setRecordingTime(int64_t time)
{
	int64_t ms = time / 10000;
	ControlUtil::setText(_timeLabel, L"%lli:%02lli:%02lli.%03lli", ms / 3600000, ms / 60000 % 60, ms / 1000 % 60, ms % 1000);
}

void RecordingDisplay::setRecordingSize(int64_t size)
{
	double quantity = (double)size;
	if (quantity < 1e6)
	{
		ControlUtil::setText(_sizeLabel, L"%.2f KB", quantity / 1e3);
	}
	else if (quantity < 1e9)
	{
		ControlUtil::setText(_sizeLabel, L"%.2f MB", quantity / 1e6);
	}
	else if (quantity < 1e12)
	{
		ControlUtil::setText(_sizeLabel, L"%.2f GB", quantity / 1e9);
	}
	else
	{
		ControlUtil::setText(_sizeLabel, L"%.2f TB", quantity / 1e12);
	}
}
