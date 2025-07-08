#include "VideoResizerFactory.h"

VideoResizerFactory::VideoResizerFactory()
{
}

const Event* VideoResizerFactory::getChangeEvent()
{
	return _settingsManager.getChangeEvent();
}

bool VideoResizerFactory::setSettings(const VideoResizerSettings& settings)
{
	return _settingsManager.setSettings(settings);
}

VideoCapture* VideoResizerFactory::createResizer(VideoCapture* source) const
{
	VideoResizerSettings settings = _settingsManager.getSettings();
	if (settings.resize)
	{
		const Buffer* inputBuffer = source->getBuffer();
		int inputWidth = inputBuffer->getWidth();
		int inputHeight = inputBuffer->getHeight();
		int outputWidth = inputWidth;
		int outputHeight = inputHeight;
		if (settings.width > 0 && settings.height > 0)
		{
			outputWidth = settings.width;
			outputHeight = settings.height;
			if (settings.keepRatio)
			{
				outputWidth = min(outputWidth, outputHeight * inputWidth / inputHeight);
				outputHeight = min(outputHeight, outputWidth * inputHeight / inputWidth);
			}
		}
		else if (settings.width > 0)
		{
			outputWidth = settings.width;
			if (settings.keepRatio)
			{
				outputHeight = outputWidth * inputHeight / inputWidth;
			}
		}
		else if (settings.height > 0)
		{
			outputHeight = settings.height;
			if (settings.keepRatio)
			{
				outputWidth = outputHeight * inputWidth / inputHeight;
			}
		}
		Vector inputSize(inputWidth, inputHeight);
		Vector outputSize(outputWidth, outputHeight);
		Resizer* resizer = createResizer(inputSize, outputSize);
		return new VideoResizer(source, outputSize, resizer);
	}
	else
	{
		return source;
	}
}

Resizer* VideoResizerFactory::createResizer(Vector inputSize, Vector outputSize) const
{
	VideoResizerSettings settings = _settingsManager.getSettings();
	int inputWidth = inputSize.x;
	int inputHeight = inputSize.y;
	int outputWidth = outputSize.x;
	int outputHeight = outputSize.y;
	if (settings.mode == ResizeModeLetterbox)
	{
		outputWidth = min(outputWidth, outputHeight * inputWidth / inputHeight);
		outputHeight = min(outputHeight, outputWidth * inputHeight / inputWidth);
	}
	if (settings.mode == ResizeModeCrop)
	{
		inputWidth = min(inputWidth, inputHeight * outputWidth / outputHeight);
		inputHeight = min(inputHeight, inputWidth * outputHeight / outputWidth);
	}
	int inputX = (inputSize.x - inputWidth) / 2;
	int inputY = (inputSize.y - inputHeight) / 2;
	int outputX = (outputSize.x - outputWidth) / 2;
	int outputY = (outputSize.y - outputHeight) / 2;
	inputX -= inputX % 2;
	inputY -= inputY % 2;
	outputX -= outputX % 2;
	outputY -= outputY % 2;
	Rect inputRect(inputX, inputY, inputX + inputWidth, inputY + inputHeight);
	Rect outputRect(outputX, outputY, outputX + outputWidth, outputY + outputHeight);
	inputSize.x = BufferUtil::alignStride(inputSize.x);
	inputSize.y = BufferUtil::alignHeight(inputSize.y);
	outputSize.x = BufferUtil::alignStride(outputSize.x);
	outputSize.y = BufferUtil::alignHeight(outputSize.y);
	switch (settings.quality)
	{
		default:
		case ResizeQualityNearest:
		{
			return new NearestResizer(inputSize, outputSize, inputRect, outputRect);
		}
		case ResizeQualityBilinear:
		{
			return new BilinearResizer(inputSize, outputSize, inputRect, outputRect);
		}
	}
}
