#pragma once

class Encoder : public FrameSink
{
public:

	Encoder(FrameSource* source, SinkWriter* sinkWriter);

	const Event* getEncodeEvent();

	const Event* getErrorEvent();

	void start();

	void stop();

	void pause();

	void resume();

	HRESULT getStatistics(MF_SINK_WRITER_STATISTICS* statistics) const;

	Status getStatus() const;

protected:

	HRESULT addStream(IMFMediaType* inputType, IMFMediaType* outputType);

	virtual HRESULT getSample(IMFSample** sample) = 0;

private:

	virtual void onFrame() override;

	virtual void onError() override;

	bool isPaused();

	HRESULT writeSample(IMFSample* sample);

	HRESULT sendStreamTick(LONGLONG timestamp);

protected:

	Status _status;

private:

	EventPool _encodeEventPool;
	EventPool _errorEventPool;
	WeakPointer<SinkWriter> _sinkWriter;
	DWORD _streamIndex;
	LONGLONG _startTime;
	LONGLONG _pauseTime;
};

