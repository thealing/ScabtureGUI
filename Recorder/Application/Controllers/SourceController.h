#pragma once

class SourceController : NonCopyable
{
public:

	SourceController(SourcePanel* sourcePanel, VideoSourceManager* videoSourceManager, AudioSourceManager* audioSourceManager);

	~SourceController();

private:

	void onVideoSourceChanged();

	void onAudioSourceChanged();

	void updateVideoSource();

	void updateAudioSource();

private:

	WindowEventDispatcher _eventDispatcher;
	WeakPointer<SourcePanel> _sourcePanel;
	WeakPointer<VideoSourceManager> _videoSourceManager;
	WeakPointer<AudioSourceManager> _audioSourceManager;
};

