#pragma once

class MouseCapture : public Capture
{
public:

	MouseCapture(const CaptureSource& source, Capture* capture, bool draw);

	virtual ~MouseCapture();

	virtual bool getFrame(Buffer* buffer) override;

private:

	void drawCursor(Buffer* buffer);

private:

	UniquePointer<Capture> _capture;
	bool _draw;
	POINT _offset;
	ICONINFO _iconInfo;
	HDC _context;
};

