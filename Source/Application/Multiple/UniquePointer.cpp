#include "UniquePointer.h"

template<class Type>
UniquePointer<Type>::UniquePointer()
{
	_object = NULL;
}

template<class Type>
UniquePointer<Type>::UniquePointer(Type* object)
{
	_object = object;
}

template<class Type>
UniquePointer<Type>::UniquePointer(UniquePointer& other)
{
	_object = other._object;
	other._object = NULL;
}

template<class Type>
UniquePointer<Type>::~UniquePointer()
{
	delete _object;
}

template<class Type>
UniquePointer<Type>& UniquePointer<Type>::operator=(Type* object)
{
	delete _object;
	_object = object;
	return *this;
}

template<class Type>
UniquePointer<Type>& UniquePointer<Type>::operator=(UniquePointer& other)
{
	delete _object;
	_object = other._object;
	other._object = NULL;
	return *this;
}

template<class Type>
Type& UniquePointer<Type>::operator*() const
{
	return *_object;
}

template<class Type>
Type* UniquePointer<Type>::operator->() const
{
	return _object;
}

template<class Type>
UniquePointer<Type>::operator Type*() const
{
	return _object;
}
