#include "RectUtil.h"

int RectUtil::getRectWidth(RECT rect)
{
	return rect.right - rect.left;
}

int RectUtil::getRectHeight(RECT rect)
{
	return rect.bottom - rect.top;
}
