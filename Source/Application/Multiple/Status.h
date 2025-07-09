#pragma once

class Status
{
public:

	Status();

	Status(HRESULT result);

	operator bool() const;

	operator HRESULT() const;

private:

	HRESULT _result;
};

