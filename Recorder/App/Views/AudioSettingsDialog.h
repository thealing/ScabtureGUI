#pragma once

class AudioSettingsDialog : public SettingsDialog<AudioSettings>
{
public:

	AudioSettingsDialog();

	~AudioSettingsDialog();

protected:

	virtual DialogWindow* createWindow(Window* parent) override;

	virtual void createControls(DialogWindow* window, AudioSettings* settings) override;
};