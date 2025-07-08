#include "RecordingPresenter.h"

RecordingPresenter::RecordingPresenter(RecordingDisplay* recordingDisplay, RecordingManager* recordingManager, VideoCaptureManager* videoCaptureManager)
{
	_recordingDisplay = recordingDisplay;
	_recordingManager = recordingManager;
	_videoCaptureManager = videoCaptureManager;
	_eventDispatcher.addEntry(recordingManager->getEncodeEvent(), BIND(RecordingPresenter, onEncodeEvent, this));
	_eventDispatcher.addEntry(videoCaptureManager->getChangeEvent(), BIND(RecordingPresenter, onCaptureChange, this));
	_eventDispatcher.start();
}

RecordingPresenter::~RecordingPresenter()
{
	_eventDispatcher.stop();
}

void RecordingPresenter::onEncodeEvent()
{
	_recordingDisplay->postTask(BIND(RecordingPresenter, update, this));
	DwmFlush();
}

void RecordingPresenter::onCaptureChange()
{
	_recordingDisplay->postTask(BIND(RecordingPresenter, reset, this));
	DwmFlush();
}

void RecordingPresenter::update()
{
	bool recording = _recordingManager->isRunning();
	if (recording)
	{
		MF_SINK_WRITER_STATISTICS videoStatistics = {};
		MF_SINK_WRITER_STATISTICS audioStatistics = {};
		_recordingManager->getVideoStatistics(&videoStatistics);
		_recordingManager->getAudioStatistics(&audioStatistics);
		LONGLONG time = max(videoStatistics.llLastTimestampEncoded, audioStatistics.llLastTimestampEncoded);
		LONGLONG size = videoStatistics.qwByteCountProcessed + audioStatistics.qwByteCountProcessed;
		_recordingDisplay->setRecordingTime(time);
		_recordingDisplay->setRecordingSize(size);
	}
}

void RecordingPresenter::reset()
{
	bool recording = _recordingManager->isRunning();
	if (!recording)
	{
		_recordingDisplay->setRecordingTime(0);
		_recordingDisplay->setRecordingSize(0);
	}
}
