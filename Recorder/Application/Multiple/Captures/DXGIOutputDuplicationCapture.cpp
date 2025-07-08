#include "DXGIOutputDuplicationCapture.h"

DXGIOutputDuplicationCapture::DXGIOutputDuplicationCapture(HWND window, POINT position, SIZE size) : WindowCapture(window)
{
	_position = position;
	createBuffer(size.cx, size.cy);
	HMONITOR monitor = MonitorFromWindow(window, MONITOR_DEFAULTTONEAREST);
	ComPointer<IDXGIDevice> dxgi;
	ComPointer<IDXGIAdapter> adapter;
	ComPointer<IDXGIOutput> output;
	ComPointer<IDXGIOutput1> output1;
	if (_status)
	{
		_status = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, NULL, 0, D3D11_SDK_VERSION, &_device, NULL, &_context);
	}
	if (_status)
	{
		_status = _device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgi);
	}
	if (_status)
	{
		_status = dxgi->GetAdapter(&adapter);
	}
	if (_status)
	{
		UINT outputIndex = 0;
		do
		{
			_status = adapter->EnumOutputs(outputIndex, &output);
			DXGI_OUTPUT_DESC desc = {};
			output->GetDesc(&desc);
			if (desc.Monitor == monitor)
			{
				break;
			}
			outputIndex++;
		}
		while (_status);
	}
	if (_status)
	{
		_status = output->QueryInterface(__uuidof(IDXGIOutput1), (void**)&output1);
	}
	if (_status)
	{
		_status = output1->DuplicateOutput(_device, &_duplication);
	}
	if (!_status)
	{
		LogUtil::logComError("DXGIOutputDuplicationCapture", _status);
	}
}

DXGIOutputDuplicationCapture::~DXGIOutputDuplicationCapture()
{
	stop();
}

bool DXGIOutputDuplicationCapture::captureFrame()
{
	if (!_status)
	{
		return false;
	}
	const Buffer* buffer = getBuffer();
	int width = buffer->getWidth();
	int height = buffer->getHeight();
	int stride = buffer->getStride();
	ComPointer<IDXGIResource> desktopResource;
	ComPointer<ID3D11Texture2D> desktopTexture;
	ComPointer<ID3D11Texture2D> captureTexture;
	DXGI_OUTDUPL_FRAME_INFO frameInfo = {};
	D3D11_TEXTURE2D_DESC desc = {};
	D3D11_MAPPED_SUBRESOURCE map = {};
	Status result;
	result = _duplication->AcquireNextFrame(INFINITE, &frameInfo, &desktopResource);
	if (result)
	{
		result = desktopResource->QueryInterface(__uuidof(ID3D11Texture2D), (void**)&desktopTexture);
	}
	if (result)
	{
		desktopTexture->GetDesc(&desc);
		desc.Usage = D3D11_USAGE_STAGING;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		desc.BindFlags = 0;
		desc.MiscFlags = 0;
		desc.Width = stride;
		desc.Height = height;
		result = _device->CreateTexture2D(&desc, NULL, &captureTexture);
	}
	if (result)
	{
		D3D11_BOX box = {};
		box.left = _position.x;
		box.top = _position.y;
		box.right = _position.x + width;
		box.bottom = _position.y + height;
		_context->CopySubresourceRegion(captureTexture, 0, 0, 0, 0, desktopTexture, 0, &box);
		result = _context->Map(captureTexture, 0, D3D11_MAP_READ, 0, &map);
	}
	if (result)
	{
		uint32_t* pixels = beginFrame();
		memcpy(pixels, (uint8_t*)map.pData, height * stride * sizeof(uint32_t));
		endFrame(result);
		_context->Unmap(captureTexture, 0);
	}
	_duplication->ReleaseFrame();
	return result;
}
