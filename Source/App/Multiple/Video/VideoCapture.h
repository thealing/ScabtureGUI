#pragma once

class VideoCapture : public virtual FrameSource
{
public:

	virtual ~VideoCapture();

	virtual const Buffer* getBuffer() const = 0;
};

