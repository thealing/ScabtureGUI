#include "SourceController.h"

SourceController::SourceController(SourcePanel* sourcePanel, VideoSourceManager* videoSourceManager, AudioSourceManager* audioSourceManager)
{
	_sourcePanel = sourcePanel;
	_videoSourceManager = videoSourceManager;
	_audioSourceManager = audioSourceManager;
	_eventDispatcher.addEntry(sourcePanel->getVideoChangeEvent(), BIND(SourceController, onVideoSourceChanged, this));
	_eventDispatcher.addEntry(sourcePanel->getAudioChangeEvent(), BIND(SourceController, onAudioSourceChanged, this));
	_eventDispatcher.addEntry(videoSourceManager->getSelectionEvent(), BIND(SourceController, updateVideoSource, this));
	_eventDispatcher.addEntry(audioSourceManager->getSelectionEvent(), BIND(SourceController, updateAudioSource, this));
	_eventDispatcher.start(sourcePanel);
	LogUtil::logDebug(L"SourceController: Started on thread %i.", _eventDispatcher.getThreadId());
}

SourceController::~SourceController()
{
	_eventDispatcher.stop();
	LogUtil::logDebug(L"SourceController: Stopped.");
}

void SourceController::onVideoSourceChanged()
{
	LogUtil::logInfo(L"SourceController: Video source selected by the user.");
	VideoSource source = (VideoSource)_sourcePanel->getVideoSource();
	_videoSourceManager->selectSource(source);
}

void SourceController::onAudioSourceChanged()
{
	LogUtil::logInfo(L"SourceController: Audio source selected by the user.");
	AudioSource source = (AudioSource)_sourcePanel->getAudioSource();
	_audioSourceManager->selectSource(source);
}

void SourceController::updateVideoSource()
{
	LogUtil::logInfo(L"SourceController: Video source changed.");
	VideoSource source = _videoSourceManager->getSource();
	_sourcePanel->setVideoSource(source);
}

void SourceController::updateAudioSource()
{
	LogUtil::logInfo(L"SourceController: Audio source changed.");
	AudioSource source = _audioSourceManager->getSource();
	_sourcePanel->setAudioSource(source);
}
