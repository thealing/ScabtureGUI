#include "MainSettingsObserver.h"

MainSettingsObserver::MainSettingsObserver(MainWindow* mainWindow, MainSettingsManager* mainSettingsManager, KeyboardListener* keyboardListener, SinkWriterFactory* sinkWriterFactory)
{
	_mainWindow = mainWindow;
	_mainSettingsManager = mainSettingsManager;
	_keyboardListener = keyboardListener;
	_sinkWriterFactory = sinkWriterFactory;
	_eventDispatcher.addEntry(mainSettingsManager->getChangeEvent(), BIND(MainSettingsObserver, onSettingsChanged, this));
	_eventDispatcher.start(mainWindow);
	LogUtil::logDebug(L"MainSettingsObserver: Started on thread %i.", _eventDispatcher.getThreadId());
}

MainSettingsObserver::~MainSettingsObserver()
{
	_eventDispatcher.stop();
	LogUtil::logDebug(L"MainSettingsObserver: Stopped.");
}

void MainSettingsObserver::onSettingsChanged()
{
	LogUtil::logInfo(L"MainSettingsObserver: Updating settings.");
	MainSettings mainSettings = _mainSettingsManager->getSettings();
	updateWindowSettings(mainSettings);
	updateKeyboardSettings(mainSettings);
	updateSinkWriterSettings(mainSettings);
	updateLoggerSettings(mainSettings);
}

void MainSettingsObserver::updateWindowSettings(const MainSettings& mainSettings)
{
	bool topMost = mainSettings.stayOnTop;
	_mainWindow->setTopMost(topMost);
}

void MainSettingsObserver::updateKeyboardSettings(const MainSettings& mainSettings)
{
	KeyboardSettings settings = {};
	settings.startHotkey = mainSettings.startHotkey;
	settings.stopHotkey = mainSettings.stopHotkey;
	settings.pauseHotkey = mainSettings.pauseHotkey;
	settings.resumeHotkey = mainSettings.resumeHotkey;
	settings.snapshotHotkey = mainSettings.snapshotHotkey;
	settings.refreshHotkey = mainSettings.refreshHotkey;
	if (_keyboardListener->setSettings(settings))
	{
		LogUtil::logInfo(L"MainSettingsObserver: Keyboard settings changed.");
	}
}

void MainSettingsObserver::updateSinkWriterSettings(const MainSettings& mainSettings)
{
	SinkWriterSettings settings = {};
	settings.lowLatency = mainSettings.lowLatencyMode;
	settings.useGpu = mainSettings.useHardwareEncoders;
	if (_sinkWriterFactory->setSettings(settings))
	{
		LogUtil::logInfo(L"MainSettingsObserver: Sink writer settings changed.");
	}
}

void MainSettingsObserver::updateLoggerSettings(const MainSettings& mainSettings)
{
	LogUtil::saveMode(mainSettings.logMode);
}
