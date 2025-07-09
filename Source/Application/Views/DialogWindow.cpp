#include "DialogWindow.h"

DialogWindow::DialogWindow(Window* parent, const wchar_t* title, int width, int height, int margin, int spacing) : CustomWindow(title)
{
	create(title, title, WS_POPUP | WS_CAPTION | WS_SYSMENU, parent);
	setSize(Vector(width, 0));
	_width = width;
	_height = height;
	_margin = margin;
	_spacing = spacing;
	_bottom = 0;
}

DialogWindow::~DialogWindow()
{
	_eventDispatcher.stop();
}

void DialogWindow::setConfirmCallback(const Callback& callback)
{
	_confirmCallback = callback;
}

void DialogWindow::setCancelCallback(const Callback& callback)
{
	_cancelCallback = callback;
}

void DialogWindow::setChangeCallback(const Callback& callback)
{
	_changeCallback = callback;
}

void DialogWindow::addCheckBox(const wchar_t* labelText, int controlWidth, bool* value)
{
	Control* label = DialogUtil::createLabel(this, labelText, _margin, _bottom + _spacing, _width - _margin - controlWidth, _height - _spacing);
	Control* control = DialogUtil::createCheckBox(this, value, _width - _margin - controlWidth, _bottom + _spacing, controlWidth, _height - _spacing);
	_eventDispatcher.addEntry(control->getChangeEvent(), _changeCallback);
	_bottom += _height;
	_controls.store(label);
	_controls.store(control);
}

void DialogWindow::addComboBox(const wchar_t* labelText, int controlWidth, int* value, const wchar_t** options, int count)
{
	Control* label = DialogUtil::createLabel(this, labelText, _margin, _bottom + _spacing, _width - _margin - controlWidth, _height - _spacing);
	Control* control = DialogUtil::createComboBox(this, value, options, count, _width - _margin - controlWidth, _bottom + _spacing, controlWidth, _height - _spacing);
	_eventDispatcher.addEntry(control->getChangeEvent(), _changeCallback);
	_bottom += _height;
	_controls.store(label);
	_controls.store(control);
}

void DialogWindow::addHotkeyEdit(const wchar_t* labelText, int controlWidth, Hotkey* value)
{
	Control* label = DialogUtil::createLabel(this, labelText, _margin, _bottom + _spacing, _width - _margin - controlWidth, _height - _spacing);
	Control* control = DialogUtil::createHotkeyEdit(this, value, _width - _margin - controlWidth, _bottom + _spacing, controlWidth, _height - _spacing);
	_eventDispatcher.addEntry(control->getChangeEvent(), _changeCallback);
	_bottom += _height;
	_controls.store(label);
	_controls.store(control);
}

void DialogWindow::addSeparator()
{
	_bottom += _spacing * 2;
	Control* control = DialogUtil::createSeparator(this, _margin, _bottom, _width - _margin * 2, 1);
	_bottom += _spacing + 1;
	_controls.store(control);
}

void DialogWindow::finalize()
{
	_bottom += 25;
	Control* confirmButton = DialogUtil::createButton(this, L"OK", _width - 90, _bottom, 80, 20);
	Control* cancelButton = DialogUtil::createButton(this, L"Cancel", _width - 180, _bottom, 80, 20);
	_bottom += 30;
	FontStore& fontStore = FontStore::getInstance();
	setChildrenFont(fontStore.getPanelFont());
	Window* parent = getParent();
	if (parent != NULL)
	{
		bool parentExcluded = parent->getExcludedFromCapture();
		setExcludedFromCapture(parentExcluded);
		Vector parentCenter = parent->getPosition() + parent->getSize() / 2;
		Vector halfSize(_width / 2, _bottom / 2);
		Rect rect(parentCenter - halfSize, parentCenter + halfSize);
		setRect(rect);
	}
	else
	{
		Vector size(_width, _bottom);
		setSize(size);
	}
	_eventDispatcher.addEntry(confirmButton->getChangeEvent(), _confirmCallback);
	_eventDispatcher.addEntry(cancelButton->getChangeEvent(), _cancelCallback);
	_eventDispatcher.start(this);
	_controls.store(confirmButton);
	_controls.store(cancelButton);
}

bool DialogWindow::canClose()
{
	_confirmCallback.invoke();
	return false;
}
