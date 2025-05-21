#pragma once

class FpsCounter : NonCopyable
{
public:

	FpsCounter();

	void reset();

	void recordFrame();

	int getMeasuredFps() const;

	const Event* getUpdateEvent() const;

private:

	void update();

private:

	mutable ReadWriteLock _lock;

	int _frameCounter;
	int _measuredFps;
	double _lastFrameTime;
	double _lastMeasureTime;
	UniquePointer<Timer> _timer;
	EventPool _updateEventPool;
};

