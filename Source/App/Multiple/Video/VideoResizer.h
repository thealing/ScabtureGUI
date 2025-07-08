#pragma once

class VideoResizer : public VideoCapture
{
public:

	VideoResizer(VideoCapture* source, Vector outputSize, Resizer* resizer);

	~VideoResizer();

private:

	void onFrame();

	void onError();

private:

	EventDispatcher _eventDispatcher;
	UniquePointer<Resizer> _resizer;
	UniquePointer<VideoCapture> _source;
};

