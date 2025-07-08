#include "VideoSourceManager.h"

VideoSourceManager::VideoSourceManager()
{
	HWND window = GetDesktopWindow();
	setFullscreenSource(window);
	_timer = new Timer(1.0, 0.05, BIND(VideoSourceManager, update, this));
}

const Event* VideoSourceManager::getChangeEvent()
{
	return _changeEventPool.getEvent();
}

const Event* VideoSourceManager::getSizeEvent()
{
	return _sizeEventPool.getEvent();
}

const Event* VideoSourceManager::getDestroyEvent()
{
	return _destroyEventPool.getEvent();
}

void VideoSourceManager::setFullscreenSource(HWND window)
{
	RECT rect = {};
	setSource(VideoSourceFullscreen, window, rect);
}

void VideoSourceManager::setRectangleSource(HWND window, RECT rect)
{
	setSource(VideoSourceRectangle, window, rect);
}

void VideoSourceManager::setWindowSource(HWND window)
{
	RECT rect = {};
	setSource(VideoSourceWindow, window, rect);
}

VideoSource VideoSourceManager::getSource() const
{
	ReadLockHolder holder(&_lock);
	return _source;
}

VideoSource VideoSourceManager::getSource(HWND* window, RECT* rect) const
{
	ReadLockHolder holder(&_lock);
	*window = _window;
	if (_source != VideoSourceRectangle)
	{
		GetClientRect(_window, rect);
	}
	else
	{
		*rect = _rect;
	}
	return _source;
}

void VideoSourceManager::setSource(VideoSource source, HWND window, RECT rect)
{
	WriteLockHolder holder(&_lock);
	_source = source;
	_window = window;
	_rect = rect;
	_size = WindowUtil::getClientSize(window);
	_changeEventPool.setEvents();
}

void VideoSourceManager::update()
{
	WriteLockHolder holder(&_lock);
	if (!IsWindow(_window))
	{
		_window = NULL;
		_destroyEventPool.setEvents();
		return;
	}
	SIZE size = WindowUtil::getClientSize(_window);
	if (!MemoryUtil::areEqual(size, _size))
	{
		_size = size;
		_sizeEventPool.setEvents();
		return;
	}
}
