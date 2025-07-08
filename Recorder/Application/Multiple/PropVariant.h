#pragma once

class PropVariant : NonCopyable
{
public:

	PropVariant();

	~PropVariant();

	PROPVARIANT* operator&();

	const PROPVARIANT* operator&() const;

	const PROPVARIANT* operator->() const;

private:

	PROPVARIANT _prop;
};

