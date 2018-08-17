#ifndef CANVAS_H_
#define CANVAS_H_

#include <cstdint>
#include <cstdio>

template<class Color>
struct MonochromeCanvas{
	constexpr static uint32_t MAX_COLORS = 255;

	uint32_t	width;
	uint32_t	height;
	Color		color;

	template<class UColor>
	constexpr MonochromeCanvas(uint32_t const width, uint32_t const height, UColor &&color) :
			width(width), height(height), color(std::forward<UColor>(color)){}

	constexpr MonochromeCanvas(uint32_t const width, uint32_t const height) :
			width(width), height(height){}

	// destructor should call foot()

	void head() const{
		printf("%s\n", "P2");
		printf("%d %d\n", width, height);
		printf("%d\n", MAX_COLORS);
	}

	constexpr static void foot(){
	}

	static void endln(){
		printf("\n");
	}

	void plot(uint32_t const value) const{
		printf("%d ", color(value));
	}
};

template<class Color>
struct RGBCanvas{
	constexpr static uint32_t MAX_COLORS = 255;

	uint32_t	width;
	uint32_t	height;
	Color		color;

	template<class UColor>
	constexpr RGBCanvas(uint32_t const width, uint32_t const height, UColor &&color) :
			width(width), height(height), color(std::forward<UColor>(color)){}

	constexpr RGBCanvas(uint32_t const width, uint32_t const height) :
			width(width), height(height){}

	// destructor should call foot()

	void head() const{
		printf("%s\n", "P3");
		printf("%d %d\n", width, height);
		printf("%d\n", MAX_COLORS);
	}

	constexpr static void foot(){
	}

	static void endln(){
		printf("\n");
	}

	void plot(uint32_t const a) const{
		const auto &c = color(a);

		printf("%d %d %d ", (int) c.r, (int) c.g, (int) c.b);
	}

};

#endif

