#ifndef TOUR_HPP_
#define TOUR_HPP_

#include "City.hpp"

class Tour
{
	private:
		int numCities;
		int tourPath[20];
		City cities[20];
		double tourValue;
		void SetCities();
	public:
		Tour();
		void SetNumCities(int numCities);
		double GetTourValue(int maxValue,City cities[]);
		void SetCityLocation(int index,int value);
		int* GetTourPath();
};

#endif //TOUR_HPP_