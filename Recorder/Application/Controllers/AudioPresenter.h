#pragma once

class AudioPresenter : NonCopyable
{
public:

	AudioPresenter(VolumeDisplay* volumeDisplay, AudioVolumeListener* audioVolumeListener, AudioSourceManager* audioSourceManager);

	~AudioPresenter();

private:

	void onUpdate();

	void onSelection();

	void updateInputState();

	void updateOutputState();

private:

	WindowEventDispatcher _eventDispatcher;
	WeakPointer<VolumeDisplay> _volumeDisplay;
	WeakPointer<AudioVolumeListener> _audioVolumeListener;
	WeakPointer<AudioSourceManager> _audioSourceManager;
};

