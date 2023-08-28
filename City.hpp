#ifndef CITY_HPP_
#define CITY_HPP_

#include <iostream>

class City
{
	private:
		double distances[20];
	public:
		City();
		void SetDistance(int element,double distance);
		double GetDistance(int e);
};

#endif // CITY_HPP_