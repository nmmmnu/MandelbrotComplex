#ifndef HUI_TABLE_H_
#define HUI_TABLE_H_

#include <cstdint>
#include <cstddef>

namespace huetable_impl_{
	template<typename T>
	struct RGB_t{
		T r;
		T g;
		T b;
	};

	struct ColorTracker{
		RGB_t<uint8_t>	value;
		RGB_t<double>	inc;
	};

	// ------------------------------

	constexpr uint8_t incChannel(uint8_t const value, double const inc, size_t const i){
		return uint8_t(value + inc * i);
	}

	constexpr RGB_t<uint8_t> incChannel(const RGB_t<uint8_t> &value, const RGB_t<double> inc, size_t const i){
		return {
			incChannel( value.r, inc.r, i),
			incChannel( value.g, inc.g, i),
			incChannel( value.b, inc.b, i)
		};
	}
} // huetable_impl_



struct HUEGradient{
	constexpr static size_t		GROUPS		= 6;
	constexpr static size_t		SIZE		= 360;
	constexpr static size_t		GROUP_SIZE	= SIZE / GROUPS;

	constexpr static uint8_t	M		= 255;
	constexpr static double		R		= M / double{ SIZE / GROUPS };

	constexpr inline static huetable_impl_::ColorTracker data[] = {
		{ { M, 0, 0 }, {  0, +R,  0 } },	//   0 to  60
		{ { M, M, 0 }, { -R,  0,  0 } },	//  60 to 120
		{ { 0, M, 0 }, {  0,  0, +R } },	// 120 to 180
		{ { 0, M, M }, {  0, -R,  0 } },	// 180 to 240
		{ { 0, 0, M }, { +R,  0,  0 } },	// 240 to 300
		{ { M, 0, M }, {  0,  0, -R } } 	// 300 to 360
	};
};



template<class Gradient>
class GradientTable{
public:
	using RGB = huetable_impl_::RGB_t<uint8_t>;

private:
	using G = Gradient;

	RGB data[G::SIZE] = {};

public:
	constexpr GradientTable(){
		size_t id = 0;

		for(const auto &ct : G::data)
			for(size_t i = 0; i < G::GROUP_SIZE; ++i)
				data[id++] = huetable_impl_::incChannel(ct.value, ct.inc, i);
	}

	constexpr const auto &operator[](size_t const i) const{
		return data[i];
	}

	constexpr static size_t size(){
		return G::SIZE;
	}
};

using HUETable = GradientTable<HUEGradient>;

#endif

