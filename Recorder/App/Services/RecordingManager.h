#pragma once

class RecordingManager : NonCopyable
{
public:

	RecordingManager();

	void start(SinkWriter* sinkWriter, Encoder* videoEncoder, Encoder* audioEncoder);

	void cleanup();

	void stop();

	void pause();

	void resume();

	bool isRunning() const;

	bool isPaused() const;

	void getVideoStatistics(MF_SINK_WRITER_STATISTICS* statistics) const;

	void getAudioStatistics(MF_SINK_WRITER_STATISTICS* statistics) const;

	const wchar_t* getPath() const;

	const FpsCounter& getFpsCounter() const;

	const Event* getEncodeEvent() const;

private:

	void onEncodedFrame();

private:

	mutable ReadWriteLock _lock;

	UniquePointer<SinkWriter> _sinkWriter;
	UniquePointer<Encoder> _videoEncoder;
	UniquePointer<Encoder> _audioEncoder;
	UniquePointer<EventDispatcher> _eventDispatcher;
	FpsCounter _fpsCounter;
	EventPool _encodeEventPool;
	bool _running;
	bool _paused;
};

