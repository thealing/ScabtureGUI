#include "VideoEncoder.h"

VideoEncoder::VideoEncoder(const VideoEncoderSettings& settings, VideoCapture* source, SinkWriter* sinkWriter) : Encoder(source, sinkWriter)
{
	_settings = settings;
	_source = source;
	ComPointer<IMFMediaType> inputType;
	ComPointer<IMFMediaType> outputType;
	if (_source == NULL)
	{
		_status = E_INVALIDARG;
	}
	if (_status)
	{
		_status = MFCreateMediaType(&inputType);
	}
	if (_status)
	{
		_status = inputType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
	}
	if (_status)
	{
		GUID format = MFVideoFormat_Base;
		switch (_settings.format)
		{
			case EncodeFormatIYUV:
			{
				format = MFVideoFormat_IYUV;
				break;
			}
			case EncodeFormatNV12:
			{
				format = MFVideoFormat_NV12;
				break;
			}
		}
		_status = inputType->SetGUID(MF_MT_SUBTYPE, format);
	}
	if (_status)
	{
		_status = inputType->SetUINT32(MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive);
	}
	if (_status)
	{
		const Buffer* buffer = _source->getBuffer();
		int stride = buffer->getStride();
		_status = inputType->SetUINT32(MF_MT_DEFAULT_STRIDE, stride);
	}
	if (_status)
	{
		const Buffer* buffer = _source->getBuffer();
		int width = buffer->getWidth();
		int height = buffer->getHeight();
		_status = MFSetAttributeSize(inputType, MF_MT_FRAME_SIZE, width, height);
	}
	if (_status)
	{
		_status = MFSetAttributeRatio(inputType, MF_MT_FRAME_RATE, _settings.frameRate, 1);
	}
	if (_status)
	{
		_status = MFCreateMediaType(&outputType);
	}
	if (_status)
	{
		_status = inputType->CopyAllItems(outputType);
	}
	if (_status)
	{
		_status = outputType->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_H264);
	}
	if (_status)
	{
		_status = outputType->SetUINT32(MF_MT_AVG_BITRATE, _settings.bitRate * 1000);
	}
	if (_status)
	{
		_status = addStream(inputType, outputType);
	}
	if (!_status)
	{
		LogUtil::logComError("VideoEncoder", _status);
	}
}

HRESULT VideoEncoder::getSample(IMFSample** sample)
{
	const Buffer* captureBuffer = _source->getBuffer();
	DWORD stride = captureBuffer->getStride();
	DWORD height = captureBuffer->getHeight();
	DWORD pixelCount = stride * height;
	DWORD encodedSize = pixelCount * 3 / 2;
	ComPointer<IMFMediaBuffer> buffer;
	BYTE* data = NULL;
	Status result;
	if (result)
	{
		result = MFCreateAlignedMemoryBuffer(encodedSize, MF_16_BYTE_ALIGNMENT, &buffer);
	}
	if (result)
	{
		result = buffer->SetCurrentLength(encodedSize);
	}
	if (result)
	{
		result = buffer->Lock(&data, NULL, NULL);
	}
	if (result)
	{
		const uint32_t* inputPixels = captureBuffer->beginReading();
		switch (_settings.format)
		{
			case EncodeFormatIYUV:
			{
				Converter::convert_bgr_to_iyuv(inputPixels, data, data + pixelCount, data + pixelCount * 5 / 4, stride, height);
				break;
			}
			case EncodeFormatNV12:
			{
				Converter::convert_bgr_to_nv12(inputPixels, data, data + pixelCount, stride, height);
				break;
			}
		}
		captureBuffer->endReading();
		result = buffer->Unlock();
	}
	if (result)
	{
		result = MFCreateSample(sample);
	}
	if (result)
	{
		result = (*sample)->AddBuffer(buffer);
	}
	if (result)
	{
		// TODO: Should this be the time when the WindowCapture::onTimer method got called?
		LONGLONG time = MFGetSystemTime();
		result = (*sample)->SetSampleTime(time);
	}
	if (result)
	{
		// TODO: Should this be the time until the next frame instead of a fixed value?
		LONGLONG duration = llround(10000000.0 / _settings.frameRate); 
		result = (*sample)->SetSampleDuration(duration);
	}
	if (!result)
	{
		LogUtil::logComWarning(__FUNCTION__, result);
	}
	return result;
}
