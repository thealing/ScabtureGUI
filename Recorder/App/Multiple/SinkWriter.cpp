#include "SinkWriter.h"

SinkWriter::SinkWriter(const SinkWriterSettings& settings, const wchar_t* path)
{
	ComPointer<IMFAttributes> attributes;
	if (_status)
	{
		_status = MFCreateAttributes(&attributes, 2);
	}
	if (_status)
	{
		_status = attributes->SetUINT32(MF_LOW_LATENCY, settings.lowLatency);
	}
	if (_status)
	{
		_status = attributes->SetUINT32(MF_READWRITE_ENABLE_HARDWARE_TRANSFORMS, settings.useGpu);
	}
	if (_status)
	{
		_status = MFCreateSinkWriterFromURL(path, NULL, attributes, &_writer);
	}
	if (!_status)
	{
		LogUtil::logComError("SinkWriter", _status);
	}
}

HRESULT SinkWriter::addStream(IMFMediaType* inputType, IMFMediaType* outputType, DWORD* streamIndex)
{
	Status result;
	if (result && _writer == NULL)
	{
		result = E_POINTER;
	}
	if (result && inputType == NULL)
	{
		result = E_INVALIDARG;
	}
	if (result && outputType == NULL)
	{
		result = E_INVALIDARG;
	}
	if (result && streamIndex == NULL)
	{
		result = E_INVALIDARG;
	}
	if (result)
	{
		result = _writer->AddStream(outputType, streamIndex);
	}
	if (result)
	{
		result = _writer->SetInputMediaType(*streamIndex, inputType, NULL);
	}
	if (!result)
	{
		LogUtil::logComError(__FUNCTION__, result);
	}
	return result;
}

HRESULT SinkWriter::writeSample(DWORD streamIndex, IMFSample* sample)
{
	Status result;
	if (result && _writer == NULL)
	{
		result = E_POINTER;
	}
	if (result && sample == NULL)
	{
		result = E_INVALIDARG;
	}
	if (result)
	{
		result = _writer->WriteSample(streamIndex, sample);
	}
	if (!result)
	{
		LogUtil::logComWarning(__FUNCTION__, result);
	}
	return result;
}

HRESULT SinkWriter::sendStreamTick(DWORD streamIndex, LONGLONG timestamp)
{
	Status result;
	if (result && _writer == NULL)
	{
		result = E_POINTER;
	}
	if (result)
	{
		result = _writer->SendStreamTick(streamIndex, timestamp);
	}
	if (!result)
	{
		LogUtil::logComWarning(__FUNCTION__, result);
	}
	return result;
}

HRESULT SinkWriter::getStatistics(DWORD streamIndex, MF_SINK_WRITER_STATISTICS* statistics)
{
	Status result;
	if (result && _writer == NULL)
	{
		result = E_POINTER;
	}
	if (result && statistics == NULL)
	{
		result = E_INVALIDARG;
	}
	if (result)
	{
		statistics->cb = sizeof(MF_SINK_WRITER_STATISTICS);
		result = _writer->GetStatistics(streamIndex, statistics);
	}
	if (!result)
	{
		LogUtil::logComWarning(__FUNCTION__, result);
	}
	return result;
}

HRESULT SinkWriter::start()
{
	Status result;
	if (result && _writer == NULL)
	{
		result = E_POINTER;
	}
	if (result)
	{
		result = _writer->BeginWriting();
	}
	if (!result)
	{
		LogUtil::logComError(__FUNCTION__, result);
	}
	return result;
}

HRESULT SinkWriter::finalize()
{
	Status result;
	if (result && _writer == NULL)
	{
		result = E_POINTER;
	}
	if (result)
	{
		result = _writer->Finalize();
	}
	if (!result)
	{
		LogUtil::logComError(__FUNCTION__, result);
	}
	return result;
}
