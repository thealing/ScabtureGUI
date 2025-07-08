#pragma once

class VideoSettingsManager : public SettingsManager<VideoSettings>
{
public:

	VideoSettingsManager();

protected:

	virtual VideoSettings getDefault() const override;

	virtual void validate(VideoSettings& settings) const override;
};

