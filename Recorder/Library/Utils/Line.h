#pragma once

class Line
{
public:

	Vector start;
	Vector end;

public:

	Line();

	Line(Vector start, Vector end);

	Line(int startX, int startY, int endX, int endY);
};


