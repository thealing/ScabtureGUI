#pragma once

class MainSettingsManager : public SettingsManager<MainSettings>
{
public:

	MainSettingsManager();

protected:

	virtual MainSettings getDefault() const override;

	virtual void validate(MainSettings& settings) const override;
};

