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

void VideoCaptureFactory::setFullscreenSource()
{
	HWND desktopWindow = GetDesktopWindow();
	RECT fullscreenRect = {};
	GetClientRect(desktopWindow, &fullscreenRect);
	setSource(NULL, fullscreenRect);
}

void VideoCaptureFactory::setRectangleSource(RECT rect)
{
	setSource(NULL, rect);
}

void VideoCaptureFactory::setWindowSource(HWND window)
{
	RECT rect = {};
	setSource(window, rect);
}

void VideoCaptureFactory::setSource(HWND window, RECT rect)
{
	WriteLockHolder holder(&_lock);
	_sourceWindow = window;
	_sourceRect = rect;
	_changeEventPool.setEvents();
}

VideoCapture* VideoCaptureFactory::createCapture() const
{
	ReadLockHolder holder(&_lock);
	if (_sourceWindow == NULL)
	{
		return new DisplayCapture(_sourceRect, _settings.frameRate, _settings.showCursor);
	}
	else
	{
		return new WindowCapture(_sourceWindow, _settings.frameRate, _settings.showCursor);
	}
}
