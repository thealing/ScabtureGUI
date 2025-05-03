#pragma once

class RecordingPresenter : NonCopyable
{
public:

	RecordingPresenter(RecordingDisplay* recordingDisplay, RecordingManager* recordingManager, VideoCaptureManager* videoCaptureManager);

	~RecordingPresenter();

private:

	void update();

	void reset();

private:

	WindowEventDispatcher _eventDispatcher;
	WeakPointer<RecordingDisplay> _recordingDisplay;
	WeakPointer<RecordingManager> _recordingManager;
	WeakPointer<VideoCaptureManager> _videoCaptureManager;
};

