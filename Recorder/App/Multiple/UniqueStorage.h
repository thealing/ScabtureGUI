#pragma once

template<class Type>
class UniqueStorage : NonCopyable
{
public:

	UniqueStorage();

	~UniqueStorage();

	void add(UniquePointer<Type>& value);

private:

	static const int Capacity = 64;

	UniquePointer<Type>* _values;
	int _count;
};

