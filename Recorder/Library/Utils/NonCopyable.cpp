#include "NonCopyable.h"

NonCopyable::NonCopyable()
{
}

NonCopyable::NonCopyable(const NonCopyable&)
{
}

NonCopyable& NonCopyable::operator=(const NonCopyable&)
{
	return *this;
}
