#pragma once

class AudioSettingsManager : public SettingsManager<AudioSettings>
{
public:

	AudioSettingsManager();

protected:

	virtual AudioSettings getDefault() const override;

	virtual void validate(AudioSettings& settings) const override;
};

