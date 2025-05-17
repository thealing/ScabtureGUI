#include "AudioResampler.h"

AudioResampler::AudioResampler(const AudioResamplerSettings& settings, AudioCapture* source) : _source(source)
{
	_inputSampleRate = 1;
	_outputSampleRate = settings.format.sampleRate;
	ComPointer<IWMResamplerProps> props;
	if (_source == NULL)
	{
		_status = E_INVALIDARG;
	}
	if (_status)
	{
		_status = source->getFormat(&_inputType);
	}
	if (_status)
	{
		_status = _inputType->GetUINT32(MF_MT_AUDIO_SAMPLES_PER_SECOND, &_inputSampleRate);
		
	}
	if (_status)
	{
		_status = MFCreateMediaType(&_outputType);
	}
	if (_status)
	{
		WaveFormat waveFormat(settings.format);
		_status = MFInitMediaTypeFromWaveFormatEx(_outputType, waveFormat, waveFormat.getSize());
	}
	if (_status)
	{
		_status = CoCreateInstance(CLSID_CResamplerMediaObject, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_resampler));
	}
	if (_status)
	{
		_status = _resampler->SetInputType(0, _inputType, 0);
	}
	if (_status)
	{
		_status = _resampler->SetOutputType(0, _outputType, 0);
	}
	if (_status)
	{
		_status = _resampler->QueryInterface(IID_PPV_ARGS(&props));
	}
	if (_status)
	{
		_status = props->SetHalfFilterLength(settings.quality);
	}
	if (_status)
	{
		_source->setCallback(BIND(AudioResampler, onFrame, this));
	}
	if (!_status)
	{
		LogUtil::logComWarning("AudioResampler", _status);
	}
}

AudioResampler::~AudioResampler()
{
}

HRESULT AudioResampler::getFormat(IMFMediaType** format)
{
	Status result;
	if (result && _outputType == NULL)
	{
		result = E_POINTER;
	}
	if (result)
	{
		_outputType->AddRef();
		*format = _outputType;
	}
	if (!result)
	{
		LogUtil::logComWarning(__FUNCTION__, result);
	}
	return result;
}

HRESULT AudioResampler::getSample(IMFSample** sample)
{
	Status result;
	ComPointer<IMFSample> inputSample;
	ComPointer<IMFMediaBuffer> inputBuffer;
	ComPointer<IMFMediaBuffer> outputBuffer;
	LONGLONG time = 0;
	LONGLONG duration = 0;
	DWORD inputSize = 0;
	if (result && _source == NULL)
	{
		result = E_POINTER;
	}
	if (result)
	{
		result = _source->getSample(&inputSample);
	}
	if (result)
	{
		result = inputSample->GetSampleTime(&time);
	}
	if (result)
	{
		result = inputSample->GetSampleDuration(&duration);
	}
	if (result)
	{
		result = inputSample->GetTotalLength(&inputSize);
	}
	if (result)
	{
		result = _resampler->ProcessInput(0, inputSample, 0);
	}
	if (result)
	{
		DWORD outputSize = BufferUtil::alignValue(inputSize * _outputSampleRate / _inputSampleRate + 1, 4);
		result = MFCreateMemoryBuffer(outputSize, &outputBuffer);
	}
	if (result)
	{
		result = MFCreateSample(sample);
	}
	if (result)
	{
		result = (*sample)->AddBuffer(outputBuffer);
	}
	if (result)
	{
		result = (*sample)->SetSampleTime(time);
	}
	if (result)
	{
		result = (*sample)->SetSampleDuration(duration);
	}
	if (result)
	{
		DWORD flags = 0;
		MFT_OUTPUT_DATA_BUFFER data = {};
		data.pSample = *sample;
		result = _resampler->ProcessOutput(0, 1, &data, &flags);
	}
	if (!result)
	{
		LogUtil::logComWarning(__FUNCTION__, result);
	}
	return result;
}

HRESULT AudioResampler::start()
{
	Status result;
	if (result && _source == NULL)
	{
		result = E_POINTER;
	}
	if (result)
	{
		result = _source->start();
	}
	if (!result)
	{
		LogUtil::logComWarning(__FUNCTION__, result);
	}
	return result;
}

HRESULT AudioResampler::stop()
{
	Status result;
	if (result && _source == NULL)
	{
		result = E_POINTER;
	}
	if (result)
	{
		result = _source->stop();
	}
	if (!result)
	{
		LogUtil::logComWarning(__FUNCTION__, result);
	}
	return result;
}

void AudioResampler::onFrame()
{
	invokeCallback();
}
