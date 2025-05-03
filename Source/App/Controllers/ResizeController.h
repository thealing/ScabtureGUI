#pragma once

class ResizeController : NonCopyable
{
public:

	ResizeController(ResizePanel* resizePanel, WindowSourceManager* windowSourceManager, VideoCaptureManager* videoCaptureManager, VideoSettingsManager* videoSettingsManager);

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
	WeakPointer<WindowSourceManager> _windowSourceManager;
	WeakPointer<VideoCaptureManager> _videoCaptureManager;
	WeakPointer<VideoSettingsManager> _videoSettingsManager;
};

