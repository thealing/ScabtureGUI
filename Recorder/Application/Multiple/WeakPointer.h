#pragma once

template<class Type>
class WeakPointer
{
public:

	WeakPointer();

	WeakPointer(Type* object);

	operator Type*() const;

	Type& operator*() const;

	Type* operator->() const;

private:

	Type* _object;
};
