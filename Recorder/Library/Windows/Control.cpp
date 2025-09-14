#include "Control.h"

Control::Control()
{
	_parent = NULL;
	_anchor = AnchorTopLeft;
	_bounds = {};
}

Control::~Control()
{
	removeCallback(controlProc);
}

void Control::setAnchor(Anchor anchor)
{
	_anchor = anchor;
	onResize();
}

void Control::setBounds(const Rect& bounds)
{
	_bounds = bounds;
	onResize();
}

void Control::setBounds(const Vector& position, const Vector& size)
{
	_bounds = Rect(position, position + size);
	onResize();
}

void Control::setBounds(int x, int y, int width, int height)
{
	_bounds = Rect(x, y, x + width, y + height);
	onResize();
}

void Control::getText(wchar_t* buffer, int size) const
{
	getTitle(buffer, size);
}

int Control::getTextLength() const
{
	return getTitleLength();
}

const Event* Control::getResizeEvent() const
{
	return &_resizeEvent;
}

const Event* Control::getChangeEvent() const
{
	return &_changeEvent;
}

void Control::create(const wchar_t* className, const wchar_t* windowName, long style, Window* parent)
{
	create(className, windowName, style, 0, parent);
}

void Control::create(const wchar_t* className, const wchar_t* windowName, long style, long exStyle, Window* parent)
{
	_parent = parent;
	Window::create(className, windowName, style, exStyle, parent);
	addCallback(controlProc);
}

Rect Control::getBounds() const
{
	return _bounds;
}

void Control::onResize()
{
	if (_parent == NULL)
	{
		return;
	}
	Vector parentSize = _parent->getSize();
	Vector position;
	switch (_anchor)
	{
		case AnchorTopLeft:
		{
			position.x = _bounds.lower.x;
			position.y = _bounds.lower.y;
			break;
		}
		case AnchorTopRight:
		{
			position.x = parentSize.x - _bounds.upper.x;
			position.y = _bounds.lower.y;
			break;
		}
		case AnchorBottomLeft:
		{
			position.x = _bounds.lower.x;
			position.y = parentSize.y - _bounds.upper.y;
			break;
		}
		case AnchorBottomRight:
		{
			position.x = parentSize.x - _bounds.upper.x;
			position.y = parentSize.y - _bounds.upper.y;
			break;
		}
		default:
		{
			return;
		}
	}
	if (position != getPosition())
	{
		setPosition(position);
	}
	Vector size = _bounds.getSize();
	if (size != Window::getSize())
	{
		setSize(size);
	}
	_resizeEvent.set();
}

void Control::onChange()
{
	_changeEvent.set();
}

LRESULT Control::controlProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR subclassId, DWORD_PTR)
{
	Control* instance = (Control*)subclassId;
	switch (message)
	{
		case MessageResized:
		{
			instance->onResize();
			break;
		}
		case MessageChanged:
		{
			instance->onChange();
			break;
		}
		case MessageSetEnabled:
		{
			bool enabled = (bool)wParam;
			instance->setEnabled(enabled);
			break;
		}
		case MessageSetForegroundColor:
		{
			Color* color = (Color*)wParam;
			instance->setForegroundColor(*color);
			break;
		}
		case MessageSetBackgroundColor:
		{
			Color* color = (Color*)wParam;
			instance->setBackgroundColor(*color);
			break;
		}
		case MessageSetFont:
		{
			Font* font = (Font*)wParam;
			instance->setFont(font);
			break;
		}
		default:
		{
			return DefSubclassProc(window, message, wParam, lParam);
		}
	}
	instance->broadcastMessage(message, wParam, lParam);
	return 0;
}
