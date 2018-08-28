#ifndef mycomplex_h_
#define mycomplex_h_

#include <type_traits>
#include <cmath>	// sqrt

template<typename T>
struct Complex{
	static_assert(std::is_floating_point<T>::value, "T must be floating point");

	using type = T;

	// ------------------------

	constexpr Complex(T const r, T const i) : data{ r, i }{};

	constexpr Complex(T const r) : Complex(r, 0){};

	constexpr Complex() : Complex(0, 0){};

	// ------------------------

	T &operator[](int const n){
		return data[n];
	}

	constexpr T operator[](int const n) const{
		return data[n];
	}

private:
	T data[2];
};

// ------------------------

template<int I, typename T>
constexpr T get(const Complex<T> &a){
	return a[I];
}

template<int I, typename T>
T &get(Complex<T> &a){
	return a[I];
}

// ------------------------

template<typename T>
constexpr bool operator==(const Complex<T> &a, const Complex<T> &b){
	return a[0] == b[0] && a[1] == b[1];
}

template<typename T>
constexpr Complex<T> operator+(const Complex<T> &a, const Complex<T> &b){
	return { a[0] + b[0], a[1] + b[1] };
}

template<typename T>
constexpr Complex<T> operator-(const Complex<T> &a, const Complex<T> &b){
	return { a[0] - b[0], a[1] - b[1] };
}

template<typename T>
constexpr Complex<T> operator*(const Complex<T> &a, const Complex<T> &b){
	// (a[0] + a[1]) * (b[0] + b[1])
	// => a[0] * b[0] + a[1] * b[0] + a[0] * b[1] + a[1] * b[1]
	// => (a[0] * b[0] - a[1] * b[1]) + (a[1] * b[0] + a[0] * b[1])
	return {
		a[0] * b[0] - a[1] * b[1],
		a[1] * b[0] + a[0] * b[1]
	};
}

// ------------------------

template<typename T>
constexpr Complex<T> operator-(const Complex<T> &a){
	return { -a[0], -a[1] };
}

template<typename T>
constexpr Complex<T> operator+(const Complex<T> &a){
	return a;
}

// ------------------------

template<typename T>
constexpr T abs2(const Complex<T> &a){
	// Pytagoras
	// a2 + b2 = c2
	return a[0] * a[0] + a[1] * a[1];
}

template<typename T>
inline T abs(const Complex<T> &a){
	// Pytagoras
	// a2 + b2 = c2
	// => c = sqrt(a2 + b2)
	return sqrt(abs2(a));
}

// ------------------------

namespace complex_impl__{
	namespace test{
		template<typename T>
		constexpr void testing(){
			using MyComplex = Complex<T>;

			constexpr MyComplex a{ 2, 3 };
			constexpr MyComplex b{ 4, 5 };

			static_assert( a + b == MyComplex{ 2 + 4,		3 + 5		},	"Complex + failed");
			static_assert( a - b == MyComplex{ 2 - 4,		3 - 5		},	"Complex - failed");
			static_assert( a * b == MyComplex{ 2 * 4 - 3 * 5,	3 * 4 + 2 * 5	},	"Complex * failed");

			static_assert(      -a == MyComplex{ -2, -3 },					"Complex u-   failed");
			static_assert(      +a == a,							"Complex u+   failed");
			static_assert( abs2(a) == 2 * 2 + 3 * 3,					"Complex abs2 failed");
		}

		constexpr void test(){
			testing<float>();
			testing<double>();
			testing<long double>();
		}
	} // namespace test
} //namespace complex_impl__

// ------------------------

using ComplexFloat  = Complex<float>;
using ComplexDouble = Complex<double>;

#endif

