#pragma once

class Encoder : public FrameSink
{
public:

	Encoder(FrameSource* source, SinkWriter* sinkWriter);

	void start();

	void stop();

	void pause();

	void resume();

	HRESULT getStatistics(MF_SINK_WRITER_STATISTICS* statistics) const;

	const Event* getEncodeEvent() const;

	const Event* getErrorEvent() const;

protected:

	HRESULT addStream(IMFMediaType* inputType, IMFMediaType* outputType);

	virtual HRESULT getSample(IMFSample** sample) = 0;

private:

	virtual void onFrame() override;

	virtual void onError() override;

	bool isPaused();

	HRESULT writeSample(IMFSample* sample);

	HRESULT sendStreamTick(LONGLONG timestamp);

private:

	EventPool _encodeEventPool;
	EventPool _errorEventPool;
	WeakPointer<SinkWriter> _sinkWriter;
	DWORD _streamIndex;
	LONGLONG _startTime;
	LONGLONG _pauseTime;
};

