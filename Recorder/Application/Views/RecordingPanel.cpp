#include "RecordingPanel.h"

RecordingPanel::RecordingPanel(Window* parent) : Panel(parent)
{
	setAnchor(AnchorBottomLeft);
	setBounds(Vector(0, 0), Vector(215, 80));
	ImageStore& imageStore = ImageStore::getInstance();
	_startButton = new CustomButton(this, imageStore.getStartImage());
	_startButton->setBounds(Vector(15, 15), Vector(50, 50));
	_stopButton = new CustomButton(this, imageStore.getStopImage());
	_stopButton->setBounds(Vector(145, 15), Vector(50, 50));
	_pauseButton = new CustomButton(this, NULL);
	_pauseButton->setBounds(Vector(80, 15), Vector(50, 50));
	FontStore& fontStore = FontStore::getInstance();
	setChildrenFont(fontStore.getPanelFont());
	setRecordingState(false);
	setPausedState(false);
}

void RecordingPanel::setRecordingState(bool recording)
{
	_startButton->setEnabled(!recording);
	_pauseButton->setEnabled(recording);
	_stopButton->setEnabled(recording);
}

void RecordingPanel::setPausedState(bool paused)
{
	ImageStore& imageStore = ImageStore::getInstance();
	if (paused)
	{
		_pauseButton->setImage(imageStore.getResumeImage());
	}
	else
	{
		_pauseButton->setImage(imageStore.getPauseImage());
	}
}

const Event* RecordingPanel::getStartClickEvent() const
{
	return _startButton->getClickEvent();
}

const Event* RecordingPanel::getStopClickEvent() const
{
	return _stopButton->getClickEvent();
}

const Event* RecordingPanel::getPauseClickEvent() const
{
	return _pauseButton->getClickEvent();
}
