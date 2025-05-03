#include "BaseResizer.h"

BaseResizer::BaseResizer(Vector outputSize, const Rect& outputRect) : _outputSize(outputSize), _outputRect(outputRect)
{
}

Vector BaseResizer::getOutputSize() const
{
    return _outputSize;
}
