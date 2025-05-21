#pragma once

class Window : NonCopyable
{
public:

	Window();

	void show();

	void hide();

	void showState(int state);

	void activate();

	void close();

	void setEnabled(bool enabled);

	void setRedraw(bool redraw);

	void repaint();

	void invalidate();

	void setPosition(Vector position);

	void setSize(Vector size);

	void setRect(const Rect& rect);

	void setText(const wchar_t* text);

	void setForegroundColor(Color color);

	void setBackgroundColor(Color color);

	void setFont(const Font* font);

	void setChildrenEnabled(bool enabled);

	void setChildrenForegroundColor(Color color);

	void setChildrenBackgroundColor(Color color);

	void setChildrenFont(const Font* font);

	void runMessageLoop();

	LRESULT sendMessage(UINT message, WPARAM wParam, LPARAM lParam);

	LRESULT postMessage(UINT message, WPARAM wParam, LPARAM lParam);

	void postTask(const Callback& callback);

	void setData(intptr_t data);

	int showMessageBox(const wchar_t* title, const wchar_t* content, UINT type) const;

	void getTitle(wchar_t* buffer, int size) const;

	int getTitleLength() const;

	Window* getParent() const;

	Window* getTopLevelParent() const;

	Vector getPosition() const;

	Vector getSize() const;

	intptr_t getData() const;

	virtual ~Window();

protected:

	void create(const wchar_t* className, const wchar_t* windowName);

	void create(const wchar_t* className, const wchar_t* windowName, long style, Window* parent);

	void create(const wchar_t* className, const wchar_t* windowName, long style, long exStyle, Window* parent);

	void addCallback(SUBCLASSPROC proc);

	void removeCallback(SUBCLASSPROC proc);

	void broadcastMessage(UINT message, WPARAM wParam, LPARAM lParam);

	HWND getHandle() const;

	HDC getContext() const;

	virtual bool canClose();

	virtual Vector getMinimumSize();

	virtual void doPaint(Graphics& graphics);

private:

	void createRenderObjects();

	void destroyRenderObjects();

private:

	HWND _handle;
	HDC _context;
	HDC _renderContext;
	HBITMAP _renderBitmap;
	Color _foregroundColor;
	Color _backgroundColor;

private:

	static Window* fromHandle(HWND handle);

	static LRESULT CALLBACK windowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR subclassId, DWORD_PTR data);

	static void excludeChildren(HWND parent, HDC context);
};
