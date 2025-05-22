#pragma once

class Capture : NonCopyable
{
public:

	virtual ~Capture();

	virtual bool getFrame(Buffer* buffer) = 0;

	void addOverlay(Overlay* overlay);

protected:

	void drawOverlays(uint32_t* pixels, int width, int height, int stride);

private:

	UniqueStorage<Overlay> _overlays;
};
