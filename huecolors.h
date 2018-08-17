#ifndef HUE_COLORS_H_
#define HUE_COLORS_H_

#include "huetable.h"

class HUEColor{
	constexpr inline static HUETable ht{};

	using RGB = HUETable::RGB<uint8_t>;

	RGB		BLACK{ 0, 0, 0 };
	uint32_t	maxInput;

public:
	constexpr HUEColor(uint32_t const maxInput) :
				maxInput(maxInput){}

	constexpr const RGB &operator()(uint32_t const a) const{
		if (a == maxInput)
			return BLACK;
		else
			return ht[a % ht.size()];
	}
};

#endif


