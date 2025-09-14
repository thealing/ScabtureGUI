#pragma once

class AudioCapture : public MediaSource
{
public:

	Status getStatus() const;

protected:

	Status _status;
};

