#pragma once

class SinkWriter : NonCopyable
{
public:

	SinkWriter(const SinkWriterSettings& settings, const wchar_t* path);

	HRESULT addStream(IMFMediaType* inputType, IMFMediaType* outputType, DWORD* streamIndex);

	HRESULT writeSample(DWORD streamIndex, IMFSample* sample);

	HRESULT sendStreamTick(DWORD streamIndex, LONGLONG timestamp);

	HRESULT getStatistics(DWORD streamIndex, MF_SINK_WRITER_STATISTICS* statistics);

	HRESULT start();

	HRESULT finalize();

	Status getStatus() const;

private:

	Status _status;
	ComPointer<IMFSinkWriter> _writer;
};

