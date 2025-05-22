#pragma once

template<class Type>
class UniqueStorage : NonCopyable
{
public:

	UniqueStorage();

	~UniqueStorage();

	void store(Type* value);

	void dispose(const Type* value);

	Type** begin();

	Type** end();

private:

	Type** _values;
	int _count;
	int _capacity;
};

