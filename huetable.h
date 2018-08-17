#include <cstdint>
#include <cstddef>

class HUETable{
public:
	template<typename T>
	struct RGB{
		T r;
		T g;
		T b;
	};

	constexpr static size_t	GROUPS	= 6;
	constexpr static size_t	SIZE	= 360;

private:
	struct ColorTracker{
		RGB<uint8_t>	value;
		RGB<int8_t>	inc;
	};

	constexpr static uint8_t	M		= 255;
	constexpr static int16_t	R		= M / 60;

	constexpr inline static ColorTracker cvtData[] = {
		{ { M, 0, 0 }, {  0, +R,  0 } },	//   0 to  60
		{ { M, M, 0 }, { -R,  0,  0 } },	//  60 to 120
		{ { 0, M, 0 }, {  0,  0, +R } },	// 120 to 180
		{ { 0, M, M }, {  0, -R,  0 } },	// 180 to 240
		{ { 0, 0, M }, { +R,  0,  0 } },	// 240 to 300
		{ { M, 0, M }, {  0,  0, -R } } 	// 300 to 360
	};

	RGB<uint8_t> data[SIZE] = {};

public:
	constexpr HUETable(){
		for(size_t group = 0; group < GROUPS; ++group){
			const auto &ct = cvtData[group];

			auto rgb = ct.value;

			for(size_t i = 0; i < SIZE / GROUPS; ++i){
				int16_t const id = group * 60 + i;

				data[id] = rgb;

				rgb.r += ct.inc.r;
				rgb.g += ct.inc.g;
				rgb.b += ct.inc.b;
			}
		}
	}

	constexpr const auto &operator[](size_t const i) const{
		return data[i];
	}

	constexpr static size_t size(){
		return SIZE;
	}

};


