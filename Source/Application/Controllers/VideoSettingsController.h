#pragma once

class VideoSettingsController : NonCopyable
{
public:

	VideoSettingsController(SourcePanel* sourcePanel, VideoSettingsDialog* videoSettingsDialog, VideoSettingsManager* videoSettingsManager);

	~VideoSettingsController();

private:

	void onButtonClicked();

	void onSettingsChanged();

private:

	WindowEventDispatcher _eventDispatcher;
	WeakPointer<SourcePanel> _sourcePanel;
	WeakPointer<VideoSettingsDialog> _videoSettingsDialog;
	WeakPointer<VideoSettingsManager> _videoSettingsManager;
};

