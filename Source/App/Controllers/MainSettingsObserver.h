#pragma once

class MainSettingsObserver : NonCopyable
{
public:

	MainSettingsObserver(MainWindow* mainWindow, MainSettingsManager* mainSettingsManager, SoundPlayer* soundPlayer, KeyboardListener* keyboardListener, SinkWriterFactory* sinkWriterFactory);

	~MainSettingsObserver();

private:

	void onSettingsChanged();

	void updateWindowSettings(const MainSettings& mainSettings);

	void updateSoundSettings(const MainSettings& mainSettings);

	void updateKeyboardSettings(const MainSettings& mainSettings);

	void updateSinkWriterSettings(const MainSettings& mainSettings);

	void updateLoggerSettings(const MainSettings& mainSettings);

private:

	WindowEventDispatcher _eventDispatcher;
	WeakPointer<MainWindow> _mainWindow;
	WeakPointer<MainSettingsManager> _mainSettingsManager;
	WeakPointer<SoundPlayer> _soundPlayer;
	WeakPointer<KeyboardListener> _keyboardListener;
	WeakPointer<SinkWriterFactory> _sinkWriterFactory;
};

