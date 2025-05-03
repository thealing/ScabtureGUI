#pragma once

class Vector
{
public:

	int x;
	int y;

public:

	Vector();

	Vector(int s);

	Vector(int x, int y);

	bool operator==(const Vector& other) const;

	bool operator!=(const Vector& other) const;

	Vector operator+(const Vector& other) const;

	Vector operator-(const Vector& other) const;

	Vector operator*(const Vector& other) const;

	Vector operator/(const Vector& other) const;

	Vector operator*(int value) const;

	Vector operator/(int value) const;
};
