#pragma once

class RecordingManager : NonCopyable
{
public:

	RecordingManager();

	const Event* getEncodeEvent();

	const Event* getVideoErrorEvent();

	const Event* getAudioErrorEvent();

	void start(SinkWriter* sinkWriter, Encoder* videoEncoder, Encoder* audioEncoder);

	void stop();

	void pause();

	void resume();

	bool isRunning() const;

	bool isPaused() const;

	void getVideoStatistics(MF_SINK_WRITER_STATISTICS* statistics) const;

	void getAudioStatistics(MF_SINK_WRITER_STATISTICS* statistics) const;

	const FpsCounter& getFpsCounter() const;

private:

	void onEncodedFrame();

	void onVideoError();

	void onAudioError();

private:

	mutable ReadWriteLock _lock;

	UniquePointer<SinkWriter> _sinkWriter;
	UniquePointer<Encoder> _videoEncoder;
	UniquePointer<Encoder> _audioEncoder;
	UniquePointer<EventDispatcher> _eventDispatcher;
	EventPool _encodeEventPool;
	EventPool _videoErrorEventPool;
	EventPool _audioErrorEventPool;
	FpsCounter _fpsCounter;
	bool _running;
	bool _paused;
};

