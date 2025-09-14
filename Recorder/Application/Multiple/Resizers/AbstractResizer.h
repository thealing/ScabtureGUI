#pragma once

class AbstractResizer : public Resizer
{
public:

	AbstractResizer(Vector outputSize, const Rect& outputRect);

	virtual Vector getOutputSize() const override;

protected:

	Vector _outputSize;
	Rect _outputRect;
};

