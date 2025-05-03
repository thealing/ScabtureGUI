#include "MemoryUtil.h"

template<typename Type>
bool MemoryUtil::areEqual(const Type& value1, const Type& value2)
{
	return memcmp(&value1, &value2, sizeof(Type)) == 0;
}
