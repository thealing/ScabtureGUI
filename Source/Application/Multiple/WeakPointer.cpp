#include "WeakPointer.h"

template<class Type>
WeakPointer<Type>::WeakPointer() 
{
	_object = NULL;
}

template<class Type>
WeakPointer<Type>::WeakPointer(Type* object) 
{
	_object = object;
}

template<class Type>
Type& WeakPointer<Type>::operator*() const 
{
	return *_object;
}

template<class Type>
Type* WeakPointer<Type>::operator->() const 
{
	return _object;
}

template<class Type>
WeakPointer<Type>::operator Type*() const 
{
	return _object;
}
