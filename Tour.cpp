#include "Tour.hpp"
#include <iostream>
#include <fstream>

Tour::Tour()
{
	for(int i = 0; i < 20; i++)
	{
		this->tourPath[i] = 0;
	}
	this->SetCities();
}

void Tour::SetCities()
{
	std::ifstream in;
	in.open("distances.txt");
	double d = 0.0;

	for(int i = 0; i < 20; i++)
	{
		for(int j = 0; j < 20; j++)
		{
			if(j == i)
			{
				this->cities[i].SetDistance(j,0.0);
				continue;
			}
			in >> d;
			this->cities[i].SetDistance(j,d);
		}
	}
	in.close();
}

void Tour::SetNumCities(int numCities)
{
	this->numCities = numCities;
}

double Tour::GetTourValue(int maxValue, City lcities[])
{
	double tourValue = 0.0;
	int i;
	for(i = 0; i < maxValue; i++)
	{
		tourValue += lcities[this->tourPath[i]].GetDistance(this->tourPath[i+1]);
	}
	tourValue += lcities[this->tourPath[i]].GetDistance(this->tourPath[0]);
	return tourValue;
}

void Tour::SetCityLocation(int index,int value)
{
	this->tourPath[index] = value;	
}

int* Tour::GetTourPath()
{
	return this->tourPath;
}