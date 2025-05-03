#include "BaseCapture.h"

BaseCapture::BaseCapture()
{
	_error = S_OK;
}

HRESULT BaseCapture::getError() const
{
	return _error;
}
