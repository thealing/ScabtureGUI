#include "Vector.h"

Vector::Vector() : x(0), y(0)
{
}

Vector::Vector(int s) : x(s), y(s)
{
}

Vector::Vector(int x, int y) : x(x), y(y)
{
}

bool Vector::operator==(const Vector& other) const
{
    return x == other.x && y == other.y;
}

bool Vector::operator!=(const Vector& other) const
{
	return !(*this == other);
}

Vector Vector::operator+(const Vector& other) const
{
	return Vector(x + other.x, y + other.y);
}

Vector Vector::operator-(const Vector& other) const
{
	return Vector(x - other.x, y - other.y);
}

Vector Vector::operator*(const Vector& other) const
{
	return Vector(x * other.x, y * other.y);
}

Vector Vector::operator/(const Vector& other) const
{
	return Vector(x / other.x, y / other.y);
}

Vector Vector::operator*(int value) const
{
    return Vector(x * value, y * value);
}

Vector Vector::operator/(int value) const
{
	return Vector(x / value, y / value);
}
