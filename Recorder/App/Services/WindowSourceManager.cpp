#include "WindowSourceManager.h"

WindowSourceManager::WindowSourceManager() : _settings(), _source()
{
}

bool WindowSourceManager::setSettings(const WindowSourceSettings& settings)
{
	WriteLockHolder holder(&_lock);
	bool init = _settingsInitEvent.set();
	if (MemoryUtil::areEqual(_settings, settings))
	{
		return false;
	}
	LogUtil::logInfo(L"WindowSourceManager: Config changed.");
	_settings = settings;
	HWND desktopWindow = WindowUtil::getDesktopWindow();
	if (desktopWindow != _source.window)
	{
		_source.rect = WindowUtil::getRelativeRect(_source.window, _settings.area);
		_source.client = _settings.area == WindowAreaClient;
	}
	if (init)
	{
		return false;
	}
	_changeEventPool.setEvents();
	return true;
}

bool WindowSourceManager::selectSource(VideoSource source)
{
	WriteLockHolder holder(&_lock);
	bool init = _sourceInitEvent.set();
	switch (source)
	{
		case VideoSourceFullscreen:
		{
			LogUtil::logInfo(L"WindowSourceManager: Selecting fullscreen.");
			HWND window = WindowUtil::getDesktopWindow();
			RECT rect = {};
			GetWindowRect(window, &rect);
			_source.window = window;
			_source.rect = rect;
			_source.client = false;
			break;
		}
		case VideoSourceRectangle:
		{
			LogUtil::logInfo(L"WindowSourceManager: Selecting rectangle.");
			RectangleSelector rectangleSelector;
			rectangleSelector.run();
			if (rectangleSelector.hasSelectedRect())
			{
				LogUtil::logInfo(L"WindowSourceManager: Rectangle selection finished.");
				_source.window = WindowUtil::getDesktopWindow();
				_source.rect = rectangleSelector.getSelectedRect();
				_source.client = false;
			}
			else
			{
				LogUtil::logInfo(L"WindowSourceManager: Rectangle selection cancelled.");
				return false;
			}
			break;
		}
		case VideoSourceWindow:
		{
			LogUtil::logInfo(L"WindowSourceManager: Selecting window.");
			WindowSelector windowSelector(_settings.area);
			windowSelector.run();
			if (windowSelector.hasSelectedWindow())
			{
				LogUtil::logInfo(L"WindowSourceManager: Window selection finished.");
				HWND window = windowSelector.getSelectedWindow();
				_source.window = window;
				_source.rect = WindowUtil::getRelativeRect(window, _settings.area);
				_source.client = _settings.area == WindowAreaClient;
			}
			else
			{
				LogUtil::logInfo(L"WindowSourceManager: Window selection cancelled.");
				return false;
			}
			break;
		}
	}
	if (init)
	{
		return false;
	}
	_changeEventPool.setEvents();
	return true;
}

Vector WindowSourceManager::getWindowSize() const
{
	_settingsInitEvent.wait();
	_sourceInitEvent.wait();
	ReadLockHolder holder(&_lock);
	int width = RectUtil::getRectWidth(_source.rect);
	int height = RectUtil::getRectHeight(_source.rect);
	return Vector(width, height);
}

VideoCapture* WindowSourceManager::createCapture() const
{
	_settingsInitEvent.wait();
	_sourceInitEvent.wait();
	ReadLockHolder holder(&_lock);
	return new WindowCapture(_settings.captureSettings, _source);
}

const Event* WindowSourceManager::getChangeEvent() const
{
	return _changeEventPool.getEvent();
}
