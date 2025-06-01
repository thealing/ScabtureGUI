#include "Date.h"

Date getDate()
{
	SYSTEMTIME systemTime;
	GetSystemTime(&systemTime);
	SystemTimeToTzSpecificLocalTime(NULL, &systemTime, &systemTime);
	Date date = {};
	date.year = systemTime.wYear;
	date.month = systemTime.wMonth;
	date.day = systemTime.wDay;
	date.hour = systemTime.wHour;
	date.minute = systemTime.wMinute;
	date.second = systemTime.wSecond;
	date.millisecond = systemTime.wMilliseconds;
	return date;
}
