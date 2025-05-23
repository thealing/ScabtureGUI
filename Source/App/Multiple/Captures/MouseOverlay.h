#pragma once

class MouseOverlay : public Overlay
{
public:

	MouseOverlay(const CaptureSource& source, bool draw);

	virtual ~MouseOverlay();

	virtual void draw(uint32_t* pixels, int width, int height, int stride) override;

private:

	bool _draw;
	HWND _window;
	bool _client;
	ICONINFO _iconInfo;
	HDC _context;
};

