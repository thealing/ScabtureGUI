#include "WaveFormat.h"

WaveFormat::WaveFormat()
{
	_waveFormat = NULL;
}

WaveFormat::WaveFormat(WaveFormat& other)
{
	_waveFormat = other._waveFormat;
	other._waveFormat = NULL;
}

WaveFormat::WaveFormat(AudioFormat format)
{
	_waveFormat = NULL;
	set(format);
}

WaveFormat::~WaveFormat()
{
	reset();
}

WaveFormat& WaveFormat::operator=(WaveFormat& other)
{
	reset();
	_waveFormat = other._waveFormat;
	other._waveFormat = NULL;
	return *this;
}

WaveFormat& WaveFormat::operator=(AudioFormat format)
{
	reset();
	set(format);
	return *this;
}

WAVEFORMATEX** WaveFormat::operator&()
{
	reset();
	return &_waveFormat;
}

const WAVEFORMATEX* WaveFormat::operator->() const
{
	return _waveFormat;
}

WaveFormat::operator const WAVEFORMATEX*() const
{
	return _waveFormat;
}

WaveFormat::operator const WAVEFORMATEX&() const
{
	return *_waveFormat;
}

int WaveFormat::getSize() const
{
	if (_waveFormat != NULL)
	{
		return sizeof(*_waveFormat) + _waveFormat->cbSize;
	}
	else
	{
		return 0;
	}
}

void WaveFormat::reset()
{
	if (_waveFormat != NULL)
	{
		CoTaskMemFree(_waveFormat);
		_waveFormat = NULL;
	}
}

void WaveFormat::set(AudioFormat format)
{
	_waveFormat = (WAVEFORMATEX*)CoTaskMemAlloc(sizeof(WAVEFORMATEX));
	if (_waveFormat != NULL)
	{
		_waveFormat->wFormatTag = WAVE_FORMAT_PCM;
		_waveFormat->nChannels = format.channelCount;
		_waveFormat->nSamplesPerSec = format.sampleRate;
		_waveFormat->wBitsPerSample = 16;
		_waveFormat->nBlockAlign = _waveFormat->nChannels * _waveFormat->wBitsPerSample / 8;
		_waveFormat->nAvgBytesPerSec = _waveFormat->nSamplesPerSec * _waveFormat->nBlockAlign;
		_waveFormat->cbSize = 0;
	}
}
