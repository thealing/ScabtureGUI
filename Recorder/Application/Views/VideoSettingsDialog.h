#pragma once

class VideoSettingsDialog : public SettingsDialog<VideoSettings>
{
public:

	VideoSettingsDialog();

	~VideoSettingsDialog();

protected:

	virtual DialogWindow* createWindow(Window* parent) override;

	virtual void createControls(DialogWindow* window, VideoSettings* settings) override;
};