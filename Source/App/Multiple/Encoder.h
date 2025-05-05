#pragma once

class Encoder : NonCopyable
{
public:

	Encoder(SinkWriter* sinkWriter);

	virtual ~Encoder();

	void start();

	void stop();

	void pause();

	void resume();

	HRESULT getStatistics(MF_SINK_WRITER_STATISTICS* statistics) const;

	const Event* getEncodeEvent() const;

protected:

	HRESULT addStream(IMFMediaType* inputType, IMFMediaType* outputType);

	void addEvent(const Event* event);

	virtual HRESULT doStart();

	virtual HRESULT doStop();

	virtual HRESULT getSample(IMFSample** sample);

private:

	void encode();

	bool isPaused();

	HRESULT writeSample(IMFSample* sample);

private:

	EventDispatcher _eventDispatcher;
	EventPool _eventPool;
	WeakPointer<SinkWriter> _sinkWriter;
	DWORD _streamIndex;
	LONGLONG _startTime;
	LONGLONG _pauseTime;
};

