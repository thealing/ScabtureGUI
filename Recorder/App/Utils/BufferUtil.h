#pragma once

class BufferUtil
{
public:

	template<class Unit>
	static Unit* allocateBuffer(int pixelCount);

	template<class Unit>
	static void freeBuffer(Unit* buffer);

	static int alignWidth(int value);

	static int alignHeight(int value);

	static int alignStride(int value);

private:

	static int alignValue(int value, int alignment);
};
