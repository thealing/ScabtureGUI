#pragma once

class MainSettingsDialog : public SettingsDialog<MainSettings>
{
public:

	MainSettingsDialog();

	~MainSettingsDialog();

protected:

	virtual DialogWindow* createWindow(Window* parent) override;

	virtual void createControls(DialogWindow* window, MainSettings* settings) override;
};

