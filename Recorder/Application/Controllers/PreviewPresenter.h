#pragma once

class PreviewPresenter : NonCopyable
{
public:

	PreviewPresenter(PreviewDisplay* previewDisplay, VideoCaptureManager* videoCaptureManager, MainSettingsManager* mainSettingsManager, VideoSettingsManager* videoSettingsManager, RecordingManager* recordingManager);

	~PreviewPresenter();

private:

	void onFrame();

	void onError();

private:

	EventDispatcher _eventDispatcher;
	WeakPointer<PreviewDisplay> _previewDisplay;
	WeakPointer<VideoCaptureManager> _videoCaptureManager;
	WeakPointer<MainSettingsManager> _mainSettingsManager;
	WeakPointer<VideoSettingsManager> _videoSettingsManager;
	WeakPointer<RecordingManager> _recordingManager;
};

