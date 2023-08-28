#ifndef DRIVER_HPP_
#define DRIVER_HPP_

#include "City.hpp"

class Driver
{
	private:
		int numCities;
		int numTours;
		int numGenerations;
		int percent;

		void GetUserInput();

	public:
		Driver();
		void Run();
};

#endif // DRIVER_HPP_