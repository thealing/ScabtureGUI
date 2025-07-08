#pragma once

class FpsPresenter : NonCopyable
{
public:

	FpsPresenter(FpsDisplay* fpsDisplay, VideoCaptureManager* videoCaptureManager, RecordingManager* recordingManager);

	~FpsPresenter();

private:

	void updateFps();

private:

	WindowEventDispatcher _eventDispatcher;
	WeakPointer<FpsDisplay> _fpsDisplay;
	WeakPointer<VideoCaptureManager> _videoCaptureManager;
	WeakPointer<RecordingManager> _recordingManager;
};

