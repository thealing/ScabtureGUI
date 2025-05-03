#pragma once

struct Date
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int millisecond;
};

void getDate(Date* date);
