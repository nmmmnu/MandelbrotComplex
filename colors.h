#ifndef COLORS_H_
#define COLORS_H_

#include <cstdint>

class NormalColor{
	constexpr static uint32_t MAX_COLORS = 255;

	uint32_t maxInput;
	double  scale;

public:
	constexpr NormalColor(uint32_t const maxInput) :
				maxInput(maxInput),
				scale(MAX_COLORS / (double) maxInput ){}

	constexpr uint32_t operator()(uint32_t const a) const{
		if (a == maxInput)
			return 0;

		return uint32_t(scale * a);
	}
};



class CosmosColor{
	constexpr static uint32_t BLACK = 0;
	constexpr static uint32_t WHITE = 255;

	constexpr inline static uint32_t COLOR[] = { BLACK, WHITE };

public:
	constexpr uint32_t operator()(uint32_t const a) const{
		return COLOR[a & 0x1];
	}
};



class CyclicColor{
	constexpr static uint32_t MAX_COLORS = 256;
	constexpr static uint32_t CYCLES = 64;
	constexpr static uint32_t SCALE  = MAX_COLORS / CYCLES;

public:
	constexpr uint32_t operator()(uint32_t const a) const{
		return (a % CYCLES) * SCALE;
	}
};

#endif


