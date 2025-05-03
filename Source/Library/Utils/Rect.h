#pragma once

class Rect
{
public:

	Vector lower;
	Vector upper;

public:

	Rect();

	Rect(Vector lower, Vector upper);

	Rect(int lowerX, int lowerY, int upperX, int upperY);

	Vector getSize() const;
};
