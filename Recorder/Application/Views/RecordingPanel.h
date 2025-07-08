#pragma once

class RecordingPanel : public Panel
{
public:

	RecordingPanel(Window* parent);

	void setRecordingState(bool recording);

	void setPausedState(bool paused);

	const Event* getStartClickEvent() const;

	const Event* getStopClickEvent() const;

	const Event* getPauseClickEvent() const;

private:

	UniquePointer<CustomButton> _startButton;
	UniquePointer<CustomButton> _stopButton;
	UniquePointer<CustomButton> _pauseButton;
};

