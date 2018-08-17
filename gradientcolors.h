#ifndef HUE_COLORS_H_
#define HUE_COLORS_H_

#include "gradienttable.h"

template<class Gradient>
class GradientColor{
	using MyGradientTable = GradientTable<Gradient>;

	constexpr inline static MyGradientTable ht{};

	using RGB = typename MyGradientTable::RGB;

	RGB		BLACK{ 0, 0, 0 };
	uint32_t	max;

public:
	constexpr GradientColor(uint32_t const max) : max(max){}

	constexpr const RGB &operator()(uint32_t const a) const{
		if (a == max)
			return BLACK;
		else
			return ht[a % ht.size()];
	}
};

using HUEColor = GradientColor<HUEGradient>;

struct ThreeGradient{
	constexpr static size_t		GROUPS		= 3;
	constexpr static size_t		GROUP_SIZE	= 64;
	constexpr static size_t		SIZE		= GROUPS * GROUP_SIZE;

	constexpr static uint8_t	M		= 255;
	constexpr static double		R		= M / double{ GROUP_SIZE };

	constexpr inline static GradientTracker data[] = {
		{ { M, 0, 0 }, { -R, +R,  0 } },
		{ { 0, M, 0 }, {  0, -R, +R } },
		{ { 0, 0, M }, { +R,  0, -R } },
	};
};

using ThreeColor = GradientColor<ThreeGradient>;

#endif

