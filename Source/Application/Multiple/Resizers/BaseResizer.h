#pragma once

class BaseResizer : public Resizer
{
public:

	BaseResizer(Vector outputSize, const Rect& outputRect);

	virtual Vector getOutputSize() const override;

protected:

	Vector _outputSize;
	Rect _outputRect;
};

