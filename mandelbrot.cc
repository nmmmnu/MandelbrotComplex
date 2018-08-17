#include "complex.h"

#include "colors.h"
#include "gradientcolors.h"
#include "canvas.h"

using MyComplex = ComplexFloat;


template<typename T>
constexpr T translate(uint32_t const a, uint32_t const max, T const r_min, T const r_max){
	T const scale = (r_max - r_min) / (T) max;
	return r_min + scale * (T) a;
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



template<class Canvas>
void mandelbrot(const Canvas &canvas, uint16_t const iterations, const MyFractalPos& pos){
	canvas.head();

	for(uint32_t y = 0; y < canvas.height; ++y){
		for(uint32_t x = 0; x < canvas.width; ++x){
			const MyComplex c = {
				translate(x, canvas.width,  pos.min_x, pos.max_x),
				translate(y, canvas.height, pos.min_y, pos.max_y)
			};

			MyComplex z = 0; // Z0

			uint16_t i = 0;
			for(; i < iterations; ++i){
				z = z * z + c;

				if (abs2(z) > 4)
					break;
			}

			canvas.plot(i);
		}

		canvas.endln();
	}

	canvas.foot();
}


constexpr uint32_t	WIDTH		= 1024;
constexpr uint32_t	HEIGHT		= 768;
constexpr double	RATIO		= WIDTH / (double) HEIGHT;
constexpr uint16_t	ITERATIONS	= 256;

constexpr MyFractalPos	MB_NORMAL		{ MyFractalPos::CreateFromRatio{}, -0.500f,  0.000f, +2.800f, RATIO };
constexpr MyFractalPos	MB_FULL			{ MyFractalPos::CreateFromRatio{}, -0.500f,  0.000f, +1.800f, RATIO };
constexpr MyFractalPos	MB_ELEPHANT_VALLEY	{ MyFractalPos::CreateFromRatio{}, +0.336f, +0.052f, +0.012f, RATIO };

constexpr MonochromeCanvas<NormalColor>	C_NORMAL	{ WIDTH, HEIGHT, ITERATIONS	};
constexpr MonochromeCanvas<CosmosColor>	C_COSMOS	{ WIDTH, HEIGHT			};
constexpr MonochromeCanvas<CyclicColor>	C_CYCLIC	{ WIDTH, HEIGHT			};
constexpr RGBCanvas<HUEColor>		C_HUE		{ WIDTH, HEIGHT, ITERATIONS	};
constexpr RGBCanvas<ThreeColor>		C_FIRE		{ WIDTH, HEIGHT, ITERATIONS	};

int main(){
	mandelbrot(C_FIRE, ITERATIONS, MB_ELEPHANT_VALLEY);
}

