#pragma once

class BufferUtil
{
public:

	template<class Unit>
	static Unit* allocateBuffer(int count);

	template<class Unit>
	static void freeBuffer(Unit* buffer);

	template<class Unit>
	static void copyBuffer(Unit* destination, const Unit* source, int count);

	static int alignValue(int value, int alignment);

	static int alignWidth(int value);

	static int alignHeight(int value);

	static int alignStride(int value);
};
