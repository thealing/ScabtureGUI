#include "RecordingPresenter.h"

RecordingPresenter::RecordingPresenter(RecordingDisplay* recordingDisplay, RecordingManager* recordingManager, VideoCaptureManager* videoCaptureManager) : _eventDispatcher(recordingDisplay)
{
	_recordingDisplay = recordingDisplay;
	_recordingManager = recordingManager;
	_videoCaptureManager = videoCaptureManager;
	_eventDispatcher.addEntry(_recordingManager->getEncodeEvent(), BIND(RecordingPresenter, update, this));
	_eventDispatcher.addEntry(_videoCaptureManager->getChangeEvent(), BIND(RecordingPresenter, reset, this));
	_eventDispatcher.start();
}

RecordingPresenter::~RecordingPresenter()
{
	_eventDispatcher.stop();
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
