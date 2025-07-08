#include "AudioSettingsObserver.h"

AudioSettingsObserver::AudioSettingsObserver(AudioSettingsManager* audioSettingsManager, AudioResamplerFactory* audioResamplerFactory, AudioEncoderFactory* audioEncoderFactory)
{
	_audioSettingsManager = audioSettingsManager;
	_audioResamplerFactory = audioResamplerFactory;
	_audioEncoderFactory = audioEncoderFactory;
	_eventDispatcher.addEntry(audioSettingsManager->getChangeEvent(), BIND(AudioSettingsObserver, onSettingsChanged, this));
	_eventDispatcher.start();
	LogUtil::logDebug(L"AudioSettingsObserver: Started on thread %i.", _eventDispatcher.getThreadId());
}

AudioSettingsObserver::~AudioSettingsObserver()
{
	_eventDispatcher.stop();
	LogUtil::logDebug(L"AudioSettingsObserver: Stopped.");
}

void AudioSettingsObserver::onSettingsChanged()
{
	LogUtil::logInfo(L"AudioSettingsObserver: Updating settings.");
	AudioSettings audioSettings = _audioSettingsManager->getSettings();
	updateAudioResamplerSettings(audioSettings);
	updateAudioEncoderSettings(audioSettings);
}

void AudioSettingsObserver::updateAudioResamplerSettings(const AudioSettings& audioSettings)
{
	AudioResamplerSettings settings = {};
	switch (audioSettings.channelLayout)
	{
		case AudioChannelLayoutStereo:
		{
			settings.format.channelCount = 2;
			break;
		}
		case AudioChannelLayoutMono:
		{
			settings.format.channelCount = 1;
			break;
		}
	}
	switch (audioSettings.sampleRate)
	{
		case AudioSampleRate44100Hz:
		{
			settings.format.sampleRate = 44100;
			break;
		}
		case AudioSampleRate48000Hz:
		{
			settings.format.sampleRate = 48000;
			break;
		}
	}
	switch (audioSettings.resampleQuality)
	{
		case AudioResampleQualityLowest:
		{
			settings.quality = 1;
			break;
		}
		case AudioResampleQualityDefault:
		{
			settings.quality = 30;
			break;
		}
		case AudioResampleQualityHighest:
		{
			settings.quality = 60;
			break;
		}
	}
	if (_audioResamplerFactory->setSettings(settings))
	{
		LogUtil::logInfo(L"AudioSettingsObserver: Audio resampler settings changed.");
	}
}

void AudioSettingsObserver::updateAudioEncoderSettings(const AudioSettings& audioSettings)
{
	AudioEncoderSettings settings = {};
	switch (audioSettings.encodeBitrate)
	{
		case AudioBitrate96Kbps:
		{
			settings.byteRate = 12000;
			break;
		}
		case AudioBitrate128Kbps:
		{
			settings.byteRate = 16000;
			break;
		}
		case AudioBitrate160Kbps:
		{
			settings.byteRate = 20000;
			break;
		}
		case AudioBitrate192Kbps:
		{
			settings.byteRate = 24000;
			break;
		}
	}
	if (_audioEncoderFactory->setSettings(settings))
	{
		LogUtil::logInfo(L"AudioSettingsObserver: Audio encoder settings changed.");
	}
}
