#ifndef __CS104_RANDOM
#define __CS104_RANDOM

#include <string>
#include <random>
#include <type_traits>

namespace cs104
{
	template<typename T>
	using EnableIfIntegral = typename std::enable_if<std::is_integral<T>::value, T>::type;

	template<typename T, typename = EnableIfIntegral<T> >
	class random_integer_number_generator
	{
	public:
		random_integer_number_generator() : mRandomNumberGenerator{ std::random_device()() } { }

		random_integer_number_generator(unsigned int seed) : mRandomNumberGenerator{ seed } { }

	public:
		T operator()()
		{
			std::uniform_int_distribution<T> distribution;
			return distribution(mRandomNumberGenerator);
		}

		T operator()(T lower, T upper)
		{
			std::uniform_int_distribution<T> distribution{ lower, upper };
			return distribution(mRandomNumberGenerator);
		}

		void seed(unsigned int seed)
		{
			mRandomNumberGenerator.seed(seed);
		}

	private:
		std::mt19937 mRandomNumberGenerator;
	};

	template<typename T>
	using EnableIfArithmetic = typename std::enable_if<std::is_arithmetic<T>::value, T>::type;

	template<typename T, typename = EnableIfArithmetic<T> >
	class random_real_number_generator
	{
	public:
		random_real_number_generator() : mRandomNumberGenerator{ std::random_device()() } { }

		random_real_number_generator(unsigned int seed) : mRandomNumberGenerator{ seed } { }

	public:
		T operator()()
		{
			std::uniform_real_distribution<T> distribution;
			return distribution(mRandomNumberGenerator);
		}

		T operator()(T lower, T upper)
		{
			std::uniform_real_distribution<T> distribution{ lower, upper };
			return distribution(mRandomNumberGenerator);
		}

		void seed(unsigned int seed)
		{
			mRandomNumberGenerator.seed(seed);
		}

	private:
		std::mt19937 mRandomNumberGenerator;
	};
}

#endif