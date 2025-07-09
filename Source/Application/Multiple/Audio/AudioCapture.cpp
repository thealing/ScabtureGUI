#include "AudioCapture.h"

AudioCapture::~AudioCapture()
{
}

Status AudioCapture::getStatus() const
{
	return _status;
}
