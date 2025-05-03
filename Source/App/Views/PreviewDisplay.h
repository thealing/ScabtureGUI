#pragma once

class PreviewDisplay : public CustomControl
{
public:

	PreviewDisplay(Window* parent);

	~PreviewDisplay();

	void invalidate();

	void setPaintCallback(const Callback& callback);

	void setDisabled(bool disabled);

	void setHighQuality(bool highQuality);

	void setUpscale(bool upscale);

	void drawPreview(const Buffer* buffer);

protected:

	virtual void onResize() override;

private:

	void updateSize(int width, int height, int stride);

	void updateControl();

	void moveControl(int x, int y, int width, int height);

	void drawPreview(const void* pixels);

	void drawPreviewDisabled();

private:

	Callback _paintCallback;
	int _timer;
	int _printTime;
	bool _dirty;
	bool _disabled;
	bool _highQuality;
	bool _upscale;
	int _width;
	int _height;
	int _stride;

private:

	static LRESULT CALLBACK subclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR subclassId, DWORD_PTR data);
};

