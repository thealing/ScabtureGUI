#include "ComPointer.h"

template<typename Object>
ComPointer<Object>::ComPointer()
{
	_object = NULL;
}

template<typename Object>
ComPointer<Object>::~ComPointer()
{
	if (_object != NULL)
	{
		_object->Release();
	}
}

template<typename Object>
Object* ComPointer<Object>::operator->() const
{
	return _object;
}

template<typename Object>
Object& ComPointer<Object>::operator*() const
{
	return *_object;
}

template<typename Object>
ComPointer<Object>::operator Object*() const
{
	return _object;
}

template<typename Object>
Object** ComPointer<Object>::operator&()
{
	if (_object)
	{
		_object->Release();
		_object = NULL;
	}
	return &_object;
}
