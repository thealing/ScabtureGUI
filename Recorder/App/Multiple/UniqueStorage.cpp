#include "UniqueStorage.h"

template<class Type>
UniqueStorage<Type>::UniqueStorage()
{
	_values = NULL;
	_count = 0;
	_capacity = 0;
}

template<class Type>
UniqueStorage<Type>::~UniqueStorage()
{
	for (int i = 0; i < _count; i++)
	{
		delete _values[i];
	}
	free(_values);
}

template<class Type>
int UniqueStorage<Type>::store(Type* value)
{
	for (int i = 0; i < _count; ++i)
	{
		if (_values[i] == NULL)
		{
			_values[i] = value;
			return i;
		}
	}
	if (_count == _capacity)
	{
		_capacity = max(4, _capacity * 2);
		_values = (Type**)_recalloc(_values, _capacity, sizeof(_values[0]));
	}
	_values[_count] = value;
	_count++;
	return _count - 1;
}

template<class Type>
int UniqueStorage<Type>::dispose(const Type* value)
{
	for (int i = 0; i < _count; ++i)
	{
		if (_values[i] == value)
		{
			delete _values[i];
			_values[i] = NULL;
			return i;
		}
	}
	return -1;
}

template<class Type>
Type* UniqueStorage<Type>::getValue(int index)
{
	return _values[index];
}

template<class Type>
const Type* UniqueStorage<Type>::getValue(int index) const
{
	return _values[index];
}

template<class Type>
const int UniqueStorage<Type>::getCount() const
{
	return _count;
}
