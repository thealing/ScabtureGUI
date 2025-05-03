#include "Math.h"

template<typename T>
T min(T a, T b)
{
	return a < b ? a : b;
}

template<typename T>
T max(T a, T b)
{
	return a > b ? a : b;
}

template<typename T>
T clamp(T x, T l, T h)
{
	return min(max(x, l), h);
}

template<typename T, typename U>
T round(U x)
{
	return (T)lround(x);
}
