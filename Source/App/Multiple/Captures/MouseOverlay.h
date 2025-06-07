#pragma once

class MouseOverlay : public Overlay
{
public:

	MouseOverlay(const CaptureSource& source);

	virtual void draw(uint32_t* pixels, int width, int height, int stride) override;

private:

	HWND _window;
	bool _client;
	POINT _offset;
};

