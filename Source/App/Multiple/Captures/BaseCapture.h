#pragma once

class BaseCapture : public Capture
{
public:

	virtual Buffer* getBuffer() override;

	virtual void addOverlay(Overlay* overlay) override;

protected:

	void createBuffer(int width, int height);

	uint32_t* beginFrame();

	void endFrame(bool result);

private:

	UniqueStorage<Overlay> _overlays;
	UniquePointer<Buffer> _buffer;
};

