#pragma once

class Capture : NonCopyable
{
public:

	virtual ~Capture();

	virtual bool getFrame() = 0;

	virtual Buffer* getBuffer() = 0;

	virtual void addOverlay(Overlay* overlay) = 0;
};
