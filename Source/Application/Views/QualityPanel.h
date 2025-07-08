#pragma once

class QualityPanel : public Panel
{
public:

	QualityPanel(Window* parent);

	void setFrameRate(int frameRate);

	void setBitRate(int bitRate);

	int getFrameRate() const;

	int getBitRate() const;

	const Event* getFrameRateChangeEvent() const;

	const Event* getBitRateChangeEvent() const;

private:

	UniquePointer<Label> _frameRateLabel;
	UniquePointer<Label> _bitRateLabel;
	UniquePointer<EditBox> _frameRateEdit;
	UniquePointer<EditBox> _bitRateEdit;
};
