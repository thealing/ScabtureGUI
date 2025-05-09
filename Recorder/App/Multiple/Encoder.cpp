#include "Encoder.h"

Encoder::Encoder(SinkWriter* sinkWriter) : _sinkWriter(sinkWriter), _streamIndex(-1), _startTime(0), _pauseTime(0)
{
}

Encoder::~Encoder()
{
}

void Encoder::start()
{
	_startTime = MFGetSystemTime();
	_eventDispatcher.start();
	doStart();
}

void Encoder::stop()
{
	doStop();
	_eventDispatcher.stop();
}

void Encoder::pause()
{
	doPause();
	_pauseTime = MFGetSystemTime();
}

void Encoder::resume()
{
	_startTime += MFGetSystemTime() - _pauseTime;
	_pauseTime = 0;
	doResume();
}

HRESULT Encoder::getStatistics(MF_SINK_WRITER_STATISTICS* statistics) const
{
	if (_sinkWriter == NULL)
	{
		return E_POINTER;
	}
	if (_streamIndex == -1)
	{
		return E_ILLEGAL_METHOD_CALL;
	}
	return _sinkWriter->getStatistics(_streamIndex, statistics);
}

const Event* Encoder::getEncodeEvent() const
{
	return _eventPool.getEvent();
}

HRESULT Encoder::addStream(IMFMediaType* inputType, IMFMediaType* outputType)
{
	if (_sinkWriter == NULL)
	{
		return E_POINTER;
	}
	if (_streamIndex != -1)
	{
		return E_ILLEGAL_METHOD_CALL;
	}
	return _sinkWriter->addStream(inputType, outputType, &_streamIndex);
}

void Encoder::addEvent(const Event* event)
{
	Callback callback = BIND(Encoder, encode, this);
	_eventDispatcher.addEntry(event, callback);
}

HRESULT Encoder::doStart()
{
	return S_OK;
}

HRESULT Encoder::doStop()
{
	return S_OK;
}

HRESULT Encoder::doPause()
{
	return S_OK;
}

HRESULT Encoder::doResume()
{
	return S_OK;
}

HRESULT Encoder::getSample(IMFSample**)
{
	return E_NOTIMPL;
}

void Encoder::encode()
{
	if (isPaused())
	{
		return;
	}
	Status result;
	ComPointer<IMFSample> sample;
	LONGLONG time = 0;
	if (result)
	{
		result = getSample(&sample);
	}
	if (result)
	{
		result = sample->GetSampleTime(&time);
	}
	if (result)
	{
		time -= _startTime;
		result = sample->SetSampleTime(time);
	}
	if (result)
	{
		result = writeSample(sample);
	}
	if (result)
	{
		_eventPool.setEvents();
	}
	if (!result)
	{
		LogUtil::logComWarning(__FUNCTION__, result);
	}
}

bool Encoder::isPaused()
{
	return _pauseTime != 0;
}

HRESULT Encoder::writeSample(IMFSample* sample)
{
	if (_sinkWriter == NULL)
	{
		return E_POINTER;
	}
	return _sinkWriter->writeSample(_streamIndex, sample);
}
