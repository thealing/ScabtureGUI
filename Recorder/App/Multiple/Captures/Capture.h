#pragma once

class Capture : NonCopyable
{
public:

	virtual ~Capture();

	virtual bool getFrame(Buffer* buffer) = 0;
};
