#pragma once

class WaveFormat
{
public:

	WaveFormat();

	WaveFormat(WaveFormat& other);

	WaveFormat(AudioFormat format);

	~WaveFormat();

	WaveFormat& operator=(WaveFormat& other);

	WaveFormat& operator=(AudioFormat format);

	WAVEFORMATEX** operator&();

	const WAVEFORMATEX* operator->() const;

	operator const WAVEFORMATEX*() const;

	operator const WAVEFORMATEX&() const;

	int getSize() const;

private:

	void reset();

	void set(AudioFormat format);

private:

	WAVEFORMATEX* _waveFormat;
};

