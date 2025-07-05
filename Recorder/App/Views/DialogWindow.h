#pragma once

class DialogWindow : public CustomWindow
{
public:

	DialogWindow(Window* parent, const wchar_t* title, int width, int height, int margin, int spacing);

	~DialogWindow();

	void setConfirmCallback(const Callback& callback);

	void setCancelCallback(const Callback& callback);

	void setChangeCallback(const Callback& callback);

	void addCheckBox(const wchar_t* labelText, int controlWidth, bool* value);

	void addComboBox(const wchar_t* labelText, int controlWidth, int* value, const wchar_t** options, int count);

	void addHotkeyEdit(const wchar_t* labelText, int controlWidth, Hotkey* value);

	void addSeparator();

	void finalize();

private:

	virtual bool canClose() override;

private:

	WindowEventDispatcher _eventDispatcher;
	UniqueStorage<Control> _controls;
	Callback _confirmCallback;
	Callback _cancelCallback;
	Callback _changeCallback;
	int _width;
	int _height;
	int _margin;
	int _spacing;
	int _bottom;
};

