#pragma once

class Color
{
public:

	uint8_t red;
	uint8_t green;
	uint8_t blue;

public:

	Color();

	Color(uint8_t shade);

	Color(uint8_t red, uint8_t green, uint8_t blue);

	operator uint32_t() const;
};
