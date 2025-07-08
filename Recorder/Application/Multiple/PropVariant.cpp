#include "PropVariant.h"

PropVariant::PropVariant()
{
	PropVariantInit(&_prop);
}

PropVariant::~PropVariant()
{
	PropVariantClear(&_prop);
}

PROPVARIANT* PropVariant::operator&()
{
	return &_prop;
}

const PROPVARIANT* PropVariant::operator&() const
{
	return &_prop;
}

const PROPVARIANT* PropVariant::operator->() const
{
	return &_prop;
}
