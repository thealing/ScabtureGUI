#pragma once

class AudioSettingsController : NonCopyable
{
public:

	AudioSettingsController(SourcePanel* sourcePanel, AudioSettingsDialog* audioSettingsDialog, AudioSettingsManager* audioSettingsManager);

	~AudioSettingsController();

private:

	void onButtonClicked();

	void onSettingsChanged();

private:

	WindowEventDispatcher _eventDispatcher;
	WeakPointer<SourcePanel> _sourcePanel;
	WeakPointer<AudioSettingsDialog> _audioSettingsDialog;
	WeakPointer<AudioSettingsManager> _audioSettingsManager;
};

