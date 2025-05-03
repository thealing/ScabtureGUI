#include "UniqueStorage.h"

template<class Type>
UniqueStorage<Type>::UniqueStorage()
{
	_values = new UniquePointer<Type>[Capacity];
	_count = 0;
}

template<class Type>
UniqueStorage<Type>::~UniqueStorage()
{
	delete[] _values;
}

template<class Type>
void UniqueStorage<Type>::add(UniquePointer<Type>& value)
{
	assert(_count < Capacity);
	_values[_count] = value;
	_count++;
}
