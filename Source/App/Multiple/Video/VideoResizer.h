#pragma once

class VideoResizer : public VideoCapture
{
public:

	VideoResizer(VideoCapture* source, Resizer* resizer, Buffer* buffer);

	virtual ~VideoResizer();

	virtual const Buffer* getBuffer() const override;

private:

	void onFrame();

private:

	EventDispatcher _eventDispatcher;
	UniquePointer<Resizer> _resizer;
	UniquePointer<Buffer> _buffer;
	UniquePointer<VideoCapture> _source;
};

