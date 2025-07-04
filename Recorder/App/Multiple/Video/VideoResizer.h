#pragma once

class VideoResizer : public FrameEmitter<VideoCapture>
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
	UniquePointer<Buffer> _buffer;
	UniquePointer<Resizer> _resizer;
	UniquePointer<VideoCapture> _source;
};

