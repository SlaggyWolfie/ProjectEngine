#include "GeneralHelpers.hpp"
#include <iostream>
#include <valarray>
#include <vector>

namespace Engine
{
	bool Random::_setup = false;

	float Random::range(const float min, const float max, int decimalAccuracy)
	{
		if (_setup) setup();

		while (std::pow(10, decimalAccuracy) >= RAND_MAX) decimalAccuracy /= 2;
		const float decimal = std::pow(10, decimalAccuracy);

		if (fabs(max - min) <= 1 / decimal)
		{
			std::cout << "Random Range Max and Min shouldn't be the same (or they're too close as float values)." << std::endl;
			return 0;
		}

		return fmod(rand() / decimal, max - min) + min;
	}

	int Random::range(const int min, const int max)
	{
		if (_setup) setup();

		if (max == min)
		{
			std::cout << "Random Range Max and Min shouldn't be the same." << std::endl;
			return 0;
		}

		return rand() % (max - min) + min;
	}

	float Random::value()
	{
		return range(0.0f, 1.0f);
	}

	void Random::setup()
	{
		srand(time(nullptr));
		_setup = true;
	}

	template <typename T>
	void List::removeFrom(std::vector<T> vector, T item)
	{
		vector.erase(
			std::remove(
				vector.begin(), vector.end(), item
			), vector.end());
	}

	template <typename T>
	bool List::contains(std::vector<T> vector, T item)
	{
		return std::find(vector.begin(), vector.end(), item) != vector.end();
	}
}