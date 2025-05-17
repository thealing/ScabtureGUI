#include "BilinearResizer.h"

BilinearResizer::BilinearResizer(Vector inputSize, Vector outputSize, const Rect& inputRect, const Rect& outputRect) : BaseResizer(outputSize, outputRect)
{
	_indexBuffer = BufferUtil::allocateBuffer<int>(outputSize.x * outputSize.y * 4);
	_weightBuffer = BufferUtil::allocateBuffer<int>(outputSize.x * outputSize.y);
	int inputWidth = inputRect.upper.x - inputRect.lower.x;
	int inputHeight = inputRect.upper.y - inputRect.lower.y;
	int outputWidth = outputRect.upper.x - outputRect.lower.x;
	int outputHeight = outputRect.upper.y - outputRect.lower.y;
	for (int outputY = 0; outputY < outputHeight; outputY++)
	{
		double inputY = (outputY + 0.5) * inputHeight / outputHeight - 0.5;
		double fractionY = inputY - floor(inputY);
		double weightsY[2] = { 1 - fractionY, fractionY };
		double indicesY[2] = { floor(inputY), ceil(inputY) };
		for (int outputX = 0; outputX < outputWidth; outputX++)
		{
			double inputX = (outputX + 0.5) * inputWidth / outputWidth - 0.5;
			double fractionX = inputX - floor(inputX);
			double weightsX[2] = { 1 - fractionX, fractionX };
			double indicesX[2] = { floor(inputX), ceil(inputX) };
			int index = outputSize.x * (outputRect.lower.y + outputY) + (outputRect.lower.x + outputX);
			for (int i = 0; i < 4; i++)
			{
				int x = round<int>(indicesX[i % 2]);
				int y = round<int>(indicesY[i / 2]);
				_indexBuffer[index * 4 + i] = inputSize.x * (inputRect.lower.y + y) + (inputRect.lower.x + x);
				double weight = (weightsX[i % 2] + weightsY[i / 2]) / 2;
				_weightBuffer[index] |= round<int>(weight * 64) << (i * 8);
			}
		}
	}
}

BilinearResizer::~BilinearResizer()
{
	BufferUtil::freeBuffer(_indexBuffer);
	BufferUtil::freeBuffer(_weightBuffer);
}

void BilinearResizer::resize(const uint32_t* inputPixels, uint32_t* outputPixels)
{
	__m128i mask1 = _mm_set_epi8(15, 11, 7, 3, 14, 10, 6, 2, 13, 9, 5, 1, 12, 8, 4, 0);
	__m128i mask2 = _mm_set_epi8(15, 14, 13, 12, 11, 10, 9, 8, 7, 3, 5, 1, 6, 4, 2, 0);
	for (int y = _outputRect.lower.y; y < _outputRect.upper.y; y++)
	{
		for (int x = _outputRect.lower.x; x < _outputRect.upper.x; x++)
		{
			int index = _outputSize.x * y + x;
			int inputIndex0 = _indexBuffer[index * 4 + 0];
			int inputIndex1 = _indexBuffer[index * 4 + 1];
			int inputIndex2 = _indexBuffer[index * 4 + 2];
			int inputIndex3 = _indexBuffer[index * 4 + 3];
			__m128i v = _mm_set_epi32(inputPixels[inputIndex3], inputPixels[inputIndex2], inputPixels[inputIndex1], inputPixels[inputIndex0]);
			__m128i w = _mm_set1_epi32(_weightBuffer[index]);
			v = _mm_shuffle_epi8(v, mask1);
			v = _mm_maddubs_epi16(v, w);
			v = _mm_hadd_epi16(v, v);
			v = _mm_srli_epi16(v, 7);
			v = _mm_shuffle_epi8(v, mask2);
			outputPixels[index] = _mm_cvtsi128_si32(v);
		}
	}
}
