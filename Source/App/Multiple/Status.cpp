#include "Status.h"

Status::Status() : _result(S_OK)
{
}

Status::Status(HRESULT result) : _result(result)
{
}

Status::operator bool() const
{
	return SUCCEEDED(_result);
}

Status::operator HRESULT() const
{
	return _result;
}
