#pragma once

class SinkWriter : NonCopyable
{
public:

	SinkWriter(const SinkWriterSettings& settings, const wchar_t* path);

	HRESULT addStream(IMFMediaType* inputType, IMFMediaType* outputType, DWORD* streamIndex);

	HRESULT writeSample(DWORD streamIndex, IMFSample* sample);

	HRESULT getStatistics(DWORD streamIndex, MF_SINK_WRITER_STATISTICS* statistics);

	HRESULT start();

	HRESULT finalize();

	const wchar_t* getPath() const;

private:

	Status _status;
	UniquePointer<const wchar_t> _path;
	ComPointer<IMFSinkWriter> _writer;
};

