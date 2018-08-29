#ifndef myquaternion_h_
#define myquaternion_h_

#include <type_traits>
#include <cmath>	// sqrt

template<typename T>
struct Quaternion{
	static_assert(std::is_floating_point<T>::value, "T must be floating point");

	using type = T;

	constexpr static unsigned char SIZE = 4;

	// ------------------------

	constexpr Quaternion(T const a0, T const a1, T const a2, T const a3) : data{ a0, a1, a2, a3 }{};

	constexpr Quaternion(T const a0, T const a1) : Quaternion(a0, a1, 0, 0){};

	constexpr Quaternion(T const a0) : Quaternion(a0, 0, 0, 0){};

	constexpr Quaternion() : Quaternion(0, 0, 0, 0){};

	// ------------------------

	T &operator[](int const n){
		return data[n];
	}

	constexpr T operator[](int const n) const{
		return data[n];
	}

private:
	T data[SIZE];
};

// ------------------------

template<int I, typename T>
constexpr T get(const Quaternion<T> &a){
	return a[I];
}

template<int I, typename T>
T &get(Quaternion<T> &a){
	return a[I];
}

// ------------------------

template<typename T>
constexpr bool operator==(const Quaternion<T> &a, const Quaternion<T> &b){
	// std::equal
	return
		a[0] == b[0] &&
		a[1] == b[1] &&
		a[2] == b[2] &&
		a[3] == b[3]
	;
}

template<typename T>
constexpr Quaternion<T> operator+(const Quaternion<T> &a, const Quaternion<T> &b){
	return {
		a[0] + b[0],
		a[1] + b[1],
		a[2] + b[2],
		a[3] + b[3]
	};
}

template<typename T>
constexpr Quaternion<T> operator-(const Quaternion<T> &a, const Quaternion<T> &b){
	return {
		a[0] - b[0],
		a[1] - b[1],
		a[2] - b[2],
		a[3] - b[3]
	};
}

template<typename T>
constexpr Quaternion<T> operator*(const Quaternion<T> &q1, const Quaternion<T> &q2){
	// https://en.wikipedia.org/wiki/Quaternion
	// Hamilton product:
	//	( a_{1}a_{2}-b_{1}b_{2}-c_{1}c_{2}-d_{1}d_{2} )
	//	( a_{1}b_{2}+b_{1}a_{2}+c_{1}d_{2}-d_{1}c_{2} ) i
	//	( a_{1}c_{2}-b_{1}d_{2}+c_{1}a_{2}+d_{1}b_{2} ) j
	//	( a_{1}d_{2}+b_{1}c_{2}-c_{1}b_{2}+d_{1}a_{2} ) k

	constexpr unsigned char a = 0;
	constexpr unsigned char b = 1;
	constexpr unsigned char c = 2;
	constexpr unsigned char d = 3;

	const auto &_1 = q1;
	const auto &_2 = q2;

	return {
		_1[a] * _2[a] - _1[b] * _2[b] - _1[c] * _2[c] - _1[d] * _2[d],
		_1[a] * _2[b] + _1[b] * _2[a] + _1[c] * _2[d] - _1[d] * _2[c],
		_1[a] * _2[c] - _1[b] * _2[d] + _1[c] * _2[a] + _1[d] * _2[b],
		_1[a] * _2[d] + _1[b] * _2[c] - _1[c] * _2[b] + _1[d] * _2[a]
	};
}

// ------------------------

template<typename T>
constexpr Quaternion<T> operator-(const Quaternion<T> &a){
	return {
		-a[0],
		-a[1],
		-a[2],
		-a[3]
	};
}

template<typename T>
constexpr Quaternion<T> operator+(const Quaternion<T> &a){
	return a;
}

// ------------------------

template<typename T>
constexpr T abs2(const Quaternion<T> &a){
	// Pytagoras
	// a2 + b2 = c2
	return
		a[0] * a[0] +
		a[1] * a[1] +
		a[2] * a[2] +
		a[3] * a[3]
	;
}

template<typename T>
inline T abs(const Quaternion<T> &a){
	// Pytagoras
	// a2 + b2 = c2
	// => c = sqrt(a2 + b2)
	return sqrt(abs2(a));
}

// ------------------------

namespace Quaternion_impl__{
	namespace test{

		template<typename T>
		constexpr void testing(){
			using MyQuaternion = Quaternion<T>;

			constexpr MyQuaternion a{ 1, 2, 3, 4 };
			constexpr MyQuaternion b{ 5, 6, 7, 8 };

			static_assert( a + b == MyQuaternion{ 1 + 5, 2 + 6, 3 + 7, 4 + 8 },	"Quaternion + failed");
			static_assert( a - b == MyQuaternion{ 1 - 5, 2 - 6, 3 - 7, 4 - 8 },	"Quaternion - failed");

			static_assert(      -a == MyQuaternion{ -1, -2, -3, -4 },		"Quaternion u-   failed");
			static_assert(      +a == a,						"Quaternion u+   failed");
			static_assert( abs2(a) == 1 * 1 + 2 * 2 + 3 * 3 + 4 * 4,		"Quaternion abs2 failed");
		}

		constexpr void test(){
			testing<float>();
			testing<double>();
			testing<long double>();
		}

	} // namespace test
} //namespace Quaternion_impl__

// ------------------------

using QuaternionFloat  = Quaternion<float>;
using QuaternionDouble = Quaternion<double>;

#endif

