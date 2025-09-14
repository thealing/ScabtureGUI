#include "NearestResizer.h"

NearestResizer::NearestResizer(Vector inputSize, Vector outputSize, const Rect& inputRect, const Rect& outputRect) : AbstractResizer(outputSize, outputRect)
{
	_indexBuffer = BufferUtil::allocateBuffer<int>(outputSize.x * outputSize.y);
	for (int y = outputRect.lower.y; y < outputRect.upper.y; y++)
	{
		for (int x = outputRect.lower.x; x < outputRect.upper.x; x++)
		{
			Vector outputPosition(x, y);
			outputPosition = outputPosition - outputRect.lower;
			Vector inputPosition = outputPosition * inputRect.getSize() / outputRect.getSize();
			inputPosition = inputPosition + inputRect.lower;
			int outputIndex = outputSize.x * y + x;
			_indexBuffer[outputIndex] = inputSize.x * inputPosition.y + inputPosition.x;
		}
	}
}

NearestResizer::~NearestResizer()
{
	BufferUtil::freeBuffer(_indexBuffer);
}

void NearestResizer::resize(const uint32_t* inputPixels, uint32_t* outputPixels)
{
	for (int y = _outputRect.lower.y; y < _outputRect.upper.y; y++)
	{
		for (int x = _outputRect.lower.x; x < _outputRect.upper.x; x++)
		{
			int index = _outputSize.x * y + x;
			int inputIndex = _indexBuffer[index];
			outputPixels[index] = inputPixels[inputIndex];
		}
	}
}
