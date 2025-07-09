#pragma once

struct AudioSettings
{
	AudioChannelLayout channelLayout;
	AudioSampleRate sampleRate;
	AudioResampleQuality resampleQuality;
	AudioBitrate encodeBitrate;
};
