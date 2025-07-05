#pragma once

class BaseCapture : public Capture
{
public:

	virtual Buffer* getBuffer() override;

	virtual void addOverlay(Overlay* overlay) override;

	virtual Status getStatus() const override;

protected:

	void createBuffer(int width, int height);

	uint32_t* beginFrame();

	void endFrame(bool result);

	void setStatus(Status status);

private:

	Status _status;
	UniqueStorage<Overlay> _overlays;
	UniquePointer<Buffer> _buffer;
};

