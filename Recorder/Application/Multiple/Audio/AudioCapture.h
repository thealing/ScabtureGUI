#pragma once

class AudioCapture : public MediaSource
{
public:

	virtual ~AudioCapture();

	Status getStatus() const;

protected:

	Status _status;
};

