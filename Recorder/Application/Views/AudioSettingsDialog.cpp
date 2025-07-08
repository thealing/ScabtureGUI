#include "AudioSettingsDialog.h"

AudioSettingsDialog::AudioSettingsDialog()
{
}

AudioSettingsDialog::~AudioSettingsDialog()
{
}

DialogWindow* AudioSettingsDialog::createWindow(Window* parent)
{
	return new DialogWindow(parent, L"Audio Options", 300, 32, 10, 6);
}

void AudioSettingsDialog::createControls(DialogWindow* window, AudioSettings* settings)
{
	const wchar_t* channelLayoutNames[AudioChannelLayoutCount] = {};
	channelLayoutNames[AudioChannelLayoutStereo] = L"Stereo";
	channelLayoutNames[AudioChannelLayoutMono] = L"Mono";
	window->addComboBox(L"Channel count", 120, (int*)&settings->channelLayout, channelLayoutNames, ARRAYSIZE(channelLayoutNames));
	const wchar_t* sampleRateNames[AudioSampleRateCount] = {};
	sampleRateNames[AudioSampleRate44100Hz] = L"44.1 KHz";
	sampleRateNames[AudioSampleRate48000Hz] = L"48 KHz";
	window->addComboBox(L"Sample rate", 120, (int*)&settings->sampleRate, sampleRateNames, ARRAYSIZE(sampleRateNames));
	const wchar_t* rasampleQualityNames[AudioResampleQualityCount] = {};
	rasampleQualityNames[AudioResampleQualityLowest] = L"Lowest";
	rasampleQualityNames[AudioResampleQualityDefault] = L"Default";
	rasampleQualityNames[AudioResampleQualityHighest] = L"Highest";
	window->addComboBox(L"Resample quality", 120, (int*)&settings->resampleQuality, rasampleQualityNames, ARRAYSIZE(rasampleQualityNames));
	const wchar_t* encodeBitrateNames[AudioBitrateCount] = {};
	encodeBitrateNames[AudioBitrate96Kbps] = L"96 Kbps";
	encodeBitrateNames[AudioBitrate128Kbps] = L"128 Kbps";
	encodeBitrateNames[AudioBitrate160Kbps] = L"160 Kbps";
	encodeBitrateNames[AudioBitrate192Kbps] = L"192 Kbps";
	window->addComboBox(L"Encode bitrate", 120, (int*)&settings->encodeBitrate, encodeBitrateNames, ARRAYSIZE(encodeBitrateNames));
}
