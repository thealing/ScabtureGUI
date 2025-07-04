#include "VideoCaptureFactory.h"

VideoCaptureFactory::VideoCaptureFactory()
{
	_settings = {};
	_sourceWindow = NULL;
	_sourceRect = {};
	setFullscreenSource();
}

const Event* VideoCaptureFactory::getChangeEvent()
{
	return _changeEventPool.getEvent();
}

bool VideoCaptureFactory::setSettings(const CaptureSettings& settings)
{
	WriteLockHolder holder(&_lock);
	if (MemoryUtil::areEqual(_settings, settings))
	{
		return false;
	}
	LogUtil::logInfo(L"VideoCaptureFactory: Settings changed.");
	_settings = settings;
	_changeEventPool.setEvents();
	return true;
}

bool VideoCaptureFactory::setFullscreenSource()
{
	HWND desktopWindow = GetDesktopWindow();
	RECT fullscreenRect = {};
	GetClientRect(desktopWindow, &fullscreenRect);
	return setSource(NULL, fullscreenRect);
}

bool VideoCaptureFactory::setRectangleSource(RECT rect)
{
	return setSource(NULL, rect);
}

bool VideoCaptureFactory::setWindowSource(HWND window)
{
	RECT rect = {};
	return setSource(window, rect);
}

bool VideoCaptureFactory::setSource(HWND window, RECT rect)
{
	WriteLockHolder holder(&_lock);
	if (_sourceWindow == window && MemoryUtil::areEqual(_sourceRect, rect))
	{
		return false;
	}
	LogUtil::logInfo(L"VideoCaptureFactory: Source changed.");
	_sourceWindow = window;
	_sourceRect = rect;
	_changeEventPool.setEvents();
	return true;
}

VideoCapture* VideoCaptureFactory::createCapture() const
{
	ReadLockHolder holder(&_lock);
	if (_sourceWindow == NULL)
	{
		//return new DisplayCapture(_sourceRect, _settings.frameRate, _settings.showCursor);
		return new WindowCapture(GetDesktopWindow(), _settings.frameRate, _settings.showCursor);
	}
	else
	{
		return new WindowCapture(_sourceWindow, _settings.frameRate, _settings.showCursor);
	}
}
