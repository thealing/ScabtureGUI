#pragma once

class MouseOverlay : public Overlay
{
public:

	MouseOverlay(HWND window, POINT offset);

	~MouseOverlay();

	virtual void draw(uint32_t* pixels, int width, int height, int stride) override;

private:

	HWND _window;
	POINT _offset;
	HDC _screenContext;
};

