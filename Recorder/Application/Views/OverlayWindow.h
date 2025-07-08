#pragma once

class OverlayWindow : NonCopyable
{
public:

	OverlayWindow(const wchar_t* title);

	void run();

	virtual ~OverlayWindow();

protected:

	void setAlpha(BYTE alpha);

	void display();

	void postMessage(UINT message, WPARAM wParam, LPARAM lParam);

	int getWidth() const;

	int getHeight() const;

	HWND getHandle() const;

	HDC getContext() const;

	virtual bool handleMessage(UINT message, WPARAM wParam, LPARAM lParam);

private:

	int _width;
	int _height;
	HWND _handle;
	HDC _context;
	HBITMAP _bitmap;
	BYTE _alpha;

private:

	static LRESULT CALLBACK windowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
};

