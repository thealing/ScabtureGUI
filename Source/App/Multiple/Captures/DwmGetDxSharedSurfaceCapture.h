#pragma once

class DwmGetDxSharedSurfaceCapture : public WindowCapture
{
public:

	DwmGetDxSharedSurfaceCapture(HWND window, POINT position, SIZE size);

	~DwmGetDxSharedSurfaceCapture();

protected:

	virtual bool captureFrame() override;

private:

	typedef HRESULT (WINAPI* DwmGetDxSharedSurface)(HWND, HANDLE*, LUID*, ULONG*, ULONG*, ULONGLONG*);

	POINT _position;
	Status _status;
	D3D11_TEXTURE2D_DESC _textureDesc;
	ComPointer<ID3D11Device> _device;
	ComPointer<ID3D11DeviceContext> _deviceContext;
	ComPointer<ID3D11Texture2D> _sharedTexture;
	ComPointer<ID3D11Texture2D> _captureTexture;
};

