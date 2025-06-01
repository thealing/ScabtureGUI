#pragma once

class VideoCapture : public FrameSource
{
public:

	virtual ~VideoCapture();

	virtual const Buffer* getBuffer() const = 0;
};

