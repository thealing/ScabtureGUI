#pragma once

// TODO: ERROR HANDLING

class BaseCapture : public Capture
{
public:

	BaseCapture();

	HRESULT getError() const;

protected:

	HRESULT _error;
};

