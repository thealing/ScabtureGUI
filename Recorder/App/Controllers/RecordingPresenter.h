#pragma once

class RecordingPresenter : NonCopyable
{
public:

	RecordingPresenter(RecordingDisplay* recordingDisplay, RecordingManager* recordingManager, VideoCaptureManager* videoCaptureManager);

	~RecordingPresenter();

private:

	void onEncodeEvent();

	void onCaptureChange();

	void update();

	void reset();

private:

	EventDispatcher _eventDispatcher;
	WeakPointer<RecordingDisplay> _recordingDisplay;
	WeakPointer<RecordingManager> _recordingManager;
	WeakPointer<VideoCaptureManager> _videoCaptureManager;
};

