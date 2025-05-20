#pragma once

template<class Type>
class UniqueStorage : NonCopyable
{
public:

	UniqueStorage();

	~UniqueStorage();

	int store(Type* value);

	int dispose(const Type* value);

	Type* getValue(int index);

	const Type* getValue(int index) const;

	const int getCount() const;

private:

	Type** _values;
	int _count;
	int _capacity;
};

