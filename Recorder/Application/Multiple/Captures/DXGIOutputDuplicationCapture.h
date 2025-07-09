#pragma once

class DXGIOutputDuplicationCapture : public WindowCapture
{
public:

	DXGIOutputDuplicationCapture(HWND window, POINT position, SIZE size);

	~DXGIOutputDuplicationCapture();

protected:

	virtual bool captureFrame() override;

private:

	POINT _position;
	Status _status;
	ComPointer<ID3D11Device> _device;
	ComPointer<ID3D11DeviceContext> _context;
	ComPointer<IDXGIOutputDuplication> _duplication;
};

