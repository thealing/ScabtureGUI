#include "Color.h"

Color::Color() : red(0), green(0), blue(0)
{
}

Color::Color(uint8_t shade) : red(shade), green(shade), blue(shade)
{
}

Color::Color(uint8_t red, uint8_t green, uint8_t blue) : red(red), green(green), blue(blue)
{
}

Color::operator uint32_t() const
{
	return RGB(red, green, blue);
}
