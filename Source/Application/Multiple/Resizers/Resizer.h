#pragma once

class Resizer : NonCopyable
{
public:

	virtual ~Resizer();

	virtual void resize(const uint32_t* inputPixels, uint32_t* outputPixels) = 0;

	virtual Vector getOutputSize() const = 0;
};

