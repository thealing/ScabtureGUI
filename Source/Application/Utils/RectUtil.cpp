#include "RectUtil.h"

int RectUtil::getRectWidth(RECT rect)
{
	return rect.right - rect.left;
}

int RectUtil::getRectHeight(RECT rect)
{
	return rect.bottom - rect.top;
}

POINT RectUtil::getRectPosition(RECT rect)
{
	POINT point = { rect.left, rect.top };
	return point;
}

SIZE RectUtil::getRectSize(RECT rect)
{
	SIZE size = { getRectWidth(rect), getRectHeight(rect) };
	return size;
}
