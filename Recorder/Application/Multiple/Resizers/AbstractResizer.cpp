#include "AbstractResizer.h"

AbstractResizer::AbstractResizer(Vector outputSize, const Rect& outputRect)
{
	_outputSize = outputSize;
	_outputRect = outputRect;
}

Vector AbstractResizer::getOutputSize() const
{
	return _outputSize;
}
