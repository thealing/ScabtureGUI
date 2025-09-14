#pragma once

template<class Type>
class WeakPointer
{
public:

	WeakPointer();

	WeakPointer(Type* object);

	Type& operator*() const;

	Type* operator->() const;

	operator Type*() const;

private:

	Type* _object;
};
