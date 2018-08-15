#include "complex.h"

#include "colors.h"

#include <cstdio>
#include <cstdint>

using MyComplex = ComplexFloat;


template<typename T>
constexpr T translate(uint32_t const a, uint32_t const max, T const r_min, T const r_max){
	T const scale = (r_max - r_min) / (T) max;
	return r_min + scale * (T) a;
}


template<class Color>
void plot(const Color &color, uint32_t const a){
	printf("%d ", color(a));
}


template<typename T>
struct FractalPos{
	T min_x;
	T max_x;
	T min_y;
	T max_y;

	struct CreateFromCoordinates{};
	struct CreateFromSize{};
	struct CreateFromRatio{};

	constexpr FractalPos(CreateFromCoordinates, T const min_x, T const max_x, T const min_y, T const max_y) :
			min_x(min_x), max_x(max_x),
			min_y(min_y), max_y(max_y){}

	constexpr FractalPos(CreateFromSize, T const x, T const y, T const size) :
			FractalPos(CreateFromSize{}, x, y, size, size){}

	constexpr FractalPos(CreateFromSize, T const x, T const y, T const sizex, T const sizey) :
			FractalPos(CreateFromCoordinates{}, x - sizex, x + sizex, y - sizey, y + sizey){}

	constexpr FractalPos(CreateFromRatio, T const x, T const y, T const sizex, double const ratio = 1.3333) :
			FractalPos(CreateFromSize{}, x, y, sizex, T(sizex / ratio)){};
};

using MyFractalPos = FractalPos<MyComplex::type>;



template<class Color>
void mandelbrot(uint32_t const width, uint32_t const height, uint16_t const iterations, const MyFractalPos& pos, const Color &color){
	printf("%s\n", "P2");
	printf("%d %d\n", width, height);
	printf("%d\n", 255);

	for(uint32_t y = 0; y < height; ++y){
		for(uint32_t x = 0; x < width; ++x){
			const MyComplex c = {
				translate(x, width,  pos.min_x, pos.max_x),
				translate(y, height, pos.min_y, pos.max_y)
			};

			MyComplex z = 0; // Z0

			uint16_t i = 0;
			for(; i < iterations; ++i){
				z = z * z + c;

				if (abs2(z) > 4)
					break;
			}

			// plot
			plot(color, i);
		}

		printf("\n");
	}
}


constexpr uint32_t	WIDTH		= 1024;
constexpr uint32_t	HEIGHT		= 768;
constexpr double_t	RATIO		= WIDTH / (double) HEIGHT;
constexpr uint16_t	ITERATIONS	= 256;

constexpr MyFractalPos	MB_FULL			{ MyFractalPos::CreateFromRatio{}, -0.500f,  0.000f, +1.800f, RATIO };
constexpr MyFractalPos	MB_ELEPHANT_VALLEY	{ MyFractalPos::CreateFromRatio{}, +0.336f, +0.052f, +0.012f, RATIO };

constexpr NormalColor	COLOR1{ ITERATIONS };
constexpr CosmosColor	COLOR2{};
constexpr CyclicColor	COLOR3{};

int main(){
	mandelbrot(WIDTH, HEIGHT, ITERATIONS, MB_ELEPHANT_VALLEY, COLOR1);
}

