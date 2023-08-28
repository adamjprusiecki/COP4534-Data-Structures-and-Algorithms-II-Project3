#include "City.hpp"

City::City()
{

}

void City::SetDistance(int element,double distance)
{
	this->distances[element] = distance;
}

double City::GetDistance(int e)
{
	return this->distances[e];
}