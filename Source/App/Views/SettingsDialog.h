#pragma once

template<class Settings>
class SettingsDialog : NonCopyable
{
public:

	SettingsDialog();

	void show(Window* parent, const Settings& settings, const Callback& callback);

	Settings getSettings() const;

	virtual ~SettingsDialog();

protected:

	virtual DialogWindow* createWindow(Window* parent) = 0;

	virtual void createControls(DialogWindow* window, Settings* settings) = 0;

private:

	void onConfirmed();

	void onCancelled();

	void onChanged();

private:

	Callback _callback;
	Settings _settings;
	Settings _oldSettings;
	UniquePointer<DialogWindow> _window;
};

