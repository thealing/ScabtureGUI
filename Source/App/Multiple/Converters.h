#pragma once

class Converter
{
public:

	static void convert_bgr_to_nv12(const uint32_t* bgr, uint8_t* y, uint8_t* uv, size_t width, size_t height);

	static void convert_bgr_to_iyuv(const uint32_t* bgr, uint8_t* y, uint8_t* u, uint8_t* v, size_t width, size_t height);

private:

	static void convert_bgr_to_y(const uint32_t* pb, uint8_t* y, __m128i m, size_t width, size_t height);

	static void convert_bgr_to_uv(const uint32_t* pb, uint8_t* uv, __m128i m, size_t width, size_t height);

	static void convert_bgr_to_uv(const uint32_t* bgr, uint8_t* u, uint8_t* v, __m128i mu, __m128i mv, size_t width, size_t height);
};

