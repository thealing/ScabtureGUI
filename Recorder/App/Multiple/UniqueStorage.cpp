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
void UniqueStorage<Type>::store(Type* value)
{
	if (_count == _capacity)
	{
		_capacity = max(4, _capacity * 2);
		_values = (Type**)_recalloc(_values, _capacity, sizeof(_values[0]));
	}
	_values[_count] = value;
	_count++;
}

template<class Type>
void UniqueStorage<Type>::dispose(const Type* value)
{
	for (int i = 0; i < _count; ++i)
	{
		if (_values[i] == value)
		{
			delete _values[i];
			for (i++; i < _count; i++)
			{
				_values[i - 1] = _values[i];
			}
			_count--;
		}
	}
}

template<class Type>
Type** UniqueStorage<Type>::begin()
{
	return _values;
}

template<class Type>
Type** UniqueStorage<Type>::end()
{
	return _values + _count;
}
