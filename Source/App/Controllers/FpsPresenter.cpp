#include "FpsPresenter.h"

FpsPresenter::FpsPresenter(FpsDisplay* fpsDisplay, VideoCaptureManager* videoCaptureManager, RecordingManager* recordingManager)
{
	_fpsDisplay = fpsDisplay;
	_videoCaptureManager = videoCaptureManager;
	_recordingManager = recordingManager;
	const FpsCounter& captureFpsCounter = _videoCaptureManager->getFpsCounter();
	const FpsCounter& encodeFpsCounter = _recordingManager->getFpsCounter();
	_eventDispatcher.addEntry(captureFpsCounter.getUpdateEvent(), BIND(FpsPresenter, updateFps, this));
	_eventDispatcher.addEntry(encodeFpsCounter.getUpdateEvent(), BIND(FpsPresenter, updateFps, this));
	_eventDispatcher.start(fpsDisplay);
}

FpsPresenter::~FpsPresenter()
{
	_eventDispatcher.stop();
}

void FpsPresenter::updateFps()
{
	const FpsCounter& captureFpsCounter = _videoCaptureManager->getFpsCounter();
	const FpsCounter& encodeFpsCounter = _recordingManager->getFpsCounter();
	int captureFps = captureFpsCounter.getMeasuredFps();
	int encodeFps = encodeFpsCounter.getMeasuredFps();
	if (!_recordingManager->isRunning())
	{
		encodeFps = captureFps;
	}
	if (_recordingManager->isPaused())
	{
		encodeFps = captureFps;
	}
	if (encodeFps < 0)
	{
		encodeFps = captureFps;
	}
	if (captureFps < 0)
	{
		captureFps = 0;
		encodeFps = 0;
	}
	_fpsDisplay->update(captureFps, encodeFps);
}
