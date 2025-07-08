#include "AudioSettingsManager.h"

AudioSettingsManager::AudioSettingsManager() : SettingsManager(L"Audio Settings")
{
	init();
}

AudioSettings AudioSettingsManager::getDefault() const
{
	AudioSettings settings = {};
	settings.channelLayout = AudioChannelLayoutStereo;
	settings.sampleRate = AudioSampleRate48000Hz;
	settings.resampleQuality = AudioResampleQualityHighest;
	settings.encodeBitrate = AudioBitrate128Kbps;
	return settings;
}

void AudioSettingsManager::validate(AudioSettings& settings) const
{
	if (settings.channelLayout < 0 || settings.channelLayout >= AudioChannelLayoutCount)
	{
		LogUtil::logWarning(L"AudioSettingsManager: Found invalid channel layout %i.", settings.channelLayout);
		settings.channelLayout = AudioChannelLayoutStereo;
	}
	if (settings.sampleRate < 0 || settings.sampleRate >= AudioSampleRateCount)
	{
		LogUtil::logWarning(L"AudioSettingsManager: Found invalid sample rate %i.", settings.sampleRate);
		settings.sampleRate = AudioSampleRate44100Hz;
	}
	if (settings.resampleQuality < 0 || settings.resampleQuality >= AudioResampleQualityCount)
	{
		LogUtil::logWarning(L"AudioSettingsManager: Found invalid resample quality %i.", settings.resampleQuality);
		settings.resampleQuality = AudioResampleQualityLowest;
	}
	if (settings.encodeBitrate < 0 || settings.encodeBitrate >= AudioBitrateCount)
	{
		LogUtil::logWarning(L"AudioSettingsManager: Found invalid encode bitrate %i.", settings.encodeBitrate);
		settings.encodeBitrate = AudioBitrate96Kbps;
	}
}
