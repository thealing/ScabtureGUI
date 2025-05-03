#pragma once

template<class Settings>
class SettingsDialog : NonCopyable
{
public:

	SettingsDialog();

	void show(Window* parent, const Settings& settings, const Callback& callback);

	const Settings* getSavedSettings() const;

	virtual ~SettingsDialog();

protected:

	virtual DialogWindow* createWindow(Window* parent) = 0;

	virtual void createControls(DialogWindow* window, Settings* settings) = 0;

private:

	void onConfirmed();

	void onCancelled();

private:

	Callback _callback;
	UniquePointer<Settings> _settings;
	UniquePointer<DialogWindow> _window;
};

