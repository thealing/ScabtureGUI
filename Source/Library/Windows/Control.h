#pragma once

class Control : public Window
{
	friend class Window;

private:

	enum : UINT
	{
		MessageNone = 0x0800,
		MessageResized,
		MessageChanged,
		MessageSetEnabled,
		MessageSetForegroundColor,
		MessageSetBackgroundColor,
		MessageSetFont,
		MessageLast
	};

public:

	Control();

	~Control();

	void setAnchor(Anchor anchor);

	void setBounds(const Rect& bounds);

	void setBounds(const Vector& position, const Vector& size);

	void setBounds(int x, int y, int width, int height);

	void getText(wchar_t* buffer, int size) const;

	int getTextLength() const;

	const Event* getResizeEvent() const;

	const Event* getChangeEvent() const;

protected:

	void create(const wchar_t* className, const wchar_t* windowName, long style, Window* parent);

	void create(const wchar_t* className, const wchar_t* windowName, long style, long exStyle, Window* parent);

	Rect getBounds() const;

	virtual void onResize();

	virtual void onChange();

private:

	Window* _parent;
	Anchor _anchor;
	Rect _bounds;
	Event _resizeEvent;
	Event _changeEvent;

private:

	static LRESULT CALLBACK controlProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR subclassId, DWORD_PTR data);
};

