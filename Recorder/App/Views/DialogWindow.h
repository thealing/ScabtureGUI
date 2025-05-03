#pragma once

class DialogWindow : public Window
{
public:

	DialogWindow(Window* parent, const wchar_t* title, int width, int height, int margin, int spacing);

	~DialogWindow();

	void setConfirmCallback(const Callback& callback);

	void setCancelCallback(const Callback& callback);

	void addCheckBox(const wchar_t* labelText, int controlWidth, bool* value);

	void addComboBox(const wchar_t* labelText, int controlWidth, int* value, const wchar_t** options, int count);

	void addHotkeyEdit(const wchar_t* labelText, int controlWidth, Hotkey* value);

	void addSeparator();

	void finalize();

protected:

	virtual void onConfirmed();

	virtual void onCancelled();

private:

	void confirm();

	void cancel();

	void confirmOnWindowThread();

	void cancelOnWindowThread();

	virtual bool canClose() override;

private:

	WindowClass _windowClass;
	Callback _confirmCallback;
	Callback _cancelCallback;
	EventDispatcher _eventDispatcher;
	UniqueStorage<Control> _controls;
	int _width;
	int _height;
	int _margin;
	int _spacing;
	int _bottom;
};

