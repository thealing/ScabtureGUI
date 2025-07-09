#pragma once

template<class Type>
class UniquePointer
{
public:

	UniquePointer();

	UniquePointer(Type* object);

	UniquePointer(UniquePointer& other);

	~UniquePointer();

	UniquePointer& operator=(Type* object);

	UniquePointer& operator=(UniquePointer& other);

	Type* get() const;

	operator Type*() const;

	Type& operator*() const;

	Type* operator->() const;

private:

	Type* _object;
};
