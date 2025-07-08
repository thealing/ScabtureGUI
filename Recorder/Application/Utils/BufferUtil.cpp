#include "BufferUtil.h"

template<class Unit>
Unit* BufferUtil::allocateBuffer(int count)
{
	int bytes = count * sizeof(Unit);
	void* buffer = _aligned_malloc(bytes, 16);
	memset(buffer, 0, bytes);
	return (Unit*)buffer;
}

template<class Unit>
void BufferUtil::freeBuffer(Unit* buffer)
{
	_aligned_free(buffer);
}

template<class Unit>
void BufferUtil::copyBuffer(Unit* destination, const Unit* source, int count)
{
	int bytes = count * sizeof(Unit);
	memcpy(destination, source, bytes);
}

int BufferUtil::alignValue(int value, int alignment)
{
	return max(alignment, (alignment + value - 1) / alignment * alignment);
}

int BufferUtil::alignWidth(int value)
{
	return alignValue(value, 2);
}

int BufferUtil::alignHeight(int value)
{
	return alignValue(value, 2);
}

int BufferUtil::alignStride(int value)
{
	return alignValue(value, 32);
}
