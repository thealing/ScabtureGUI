#pragma once

class RecordingDisplay : public Frame
{
public:

	RecordingDisplay(Window* parent);

	void setRecordingTime(int64_t time);

	void setRecordingSize(int64_t size);

private:

	UniquePointer<Label> _timeLabel;
	UniquePointer<Label> _sizeLabel;
};

