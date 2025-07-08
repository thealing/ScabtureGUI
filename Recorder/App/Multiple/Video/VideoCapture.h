#pragma once

class VideoCapture : public FrameEmitter<FrameSource>
{
public:

	VideoCapture();

	void addOverlay(Overlay* overlay);

	const Buffer* getBuffer() const;

protected:

	void createBuffer(int width, int height);

	uint32_t* beginFrame();

	void endFrame(bool success);

private:

	UniquePointer<Buffer> _buffer;
	UniqueStorage<Overlay> _overlays;
};

