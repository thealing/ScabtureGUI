#pragma once

class VideoResizer : public FrameEmitter, public virtual VideoCapture
{
public:

	VideoResizer(VideoCapture* source, Resizer* resizer, Buffer* buffer);

	virtual ~VideoResizer();

	virtual const Buffer* getBuffer() const override;

private:

	void onFrame();

	void onError();

private:

	EventDispatcher _eventDispatcher;
	UniquePointer<Resizer> _resizer;
	UniquePointer<Buffer> _buffer;
	UniquePointer<VideoCapture> _source;
};

