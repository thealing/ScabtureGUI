#pragma once

class ResizeController : NonCopyable
{
public:

	ResizeController(ResizePanel* resizePanel, VideoCaptureFactory* videoCaptureFactory, VideoCaptureManager* videoCaptureManager, VideoSettingsManager* videoSettingsManager);

	~ResizeController();

private:

	void onWidthChanged();

	void onHeightChanged();

	void onResizeChanged();

	void onKeepRatioChanged();

	void onVideoCaptureChanged();

	void onVideoSettingsChanged();

private:

	WindowEventDispatcher _eventDispatcher;
	WeakPointer<ResizePanel> _resizePanel;
	WeakPointer<VideoCaptureFactory> _videoCaptureFactory;
	WeakPointer<VideoCaptureManager> _videoCaptureManager;
	WeakPointer<VideoSettingsManager> _videoSettingsManager;
};

