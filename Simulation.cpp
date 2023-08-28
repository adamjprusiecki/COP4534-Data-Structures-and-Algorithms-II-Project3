#include "Simulation.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>

#include "Tour.hpp"

Simulation::Simulation(int numOfCities,int numTours,int numGenerations, int percent)
{
	this->GenerateCities();
	this->numOfCities = numOfCities;
	this->numTours = numTours;
	this->numGenerations = numGenerations;
	this->percent = percent;
}

void Simulation::GenerateCities()
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

unsigned long int Simulation::GetFactorial(int num) // For Brute Force Calculation
{
	unsigned long int factorial = 1;
	if(num == 1)
	{
		return factorial;
	}
	for(int i = 1; i < num + 1; i++)
	{
		factorial = factorial * i;
	}

	return factorial;
}

void Simulation::BruteForce()
{
	int cityPath[this->numOfCities];
	int finalPath[this->numOfCities]; 
	for(int i = 0; i < this->numOfCities; i++)
	{
		cityPath[i] = i; 
		finalPath[i] = i;
	}

	//GetStartTime
	auto startTime = std::chrono::high_resolution_clock::now();
	
	//BruteForceStart
	double lowestTour = 10000000000000000.0;
	double currentTour = 0.0;

	unsigned long int index = 0;
	unsigned long int nMinusOneFactorial = this->GetFactorial(this->numOfCities - 1); 
	int j = 0;
	do
	{
		index++;

		for(j = 0; j < this->numOfCities; j++)
		{
			currentTour += this->cities[cityPath[j]].GetDistance(cityPath[j+1]);
		}
		currentTour += this->cities[cityPath[j]].GetDistance(cityPath[0]);
		if(currentTour < lowestTour)
		{
			lowestTour = currentTour;
			for(int i = 0; i < this->numOfCities; i++)
			{
				finalPath[i] = cityPath[i];
			}
		}
		currentTour = 0.0;
		std::next_permutation(cityPath,cityPath+this->numOfCities);
	}
	while(index != nMinusOneFactorial);

	this->bruteForceCost = lowestTour;
	
	//GetEndTime
	auto endTime = std::chrono::high_resolution_clock::now();
	auto durationSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

	this->bruteForceTimeInSec = std::chrono::duration<double>(durationSeconds).count();
}

Tour Simulation::Mutate(int tourPath[],Tour tempTour)
{
	std::random_shuffle(&tourPath[2],&tourPath[this->numOfCities]);

	for(int i = 0; i < this->numOfCities; i++)
	{
		tempTour.SetCityLocation(i,tourPath[i]);
	}

	return tempTour;
	
}

std::vector<Tour> Simulation::MakeNextGeneration(int numOfMutations,std::vector<Tour> oldTours,Tour elite1, Tour elite2)
{
	std::vector<Tour> newTours;
	Tour tempTour;
	tempTour.SetNumCities(this->numOfCities);
	for(int i = 0; i < numTours; i++)
	{
		newTours.push_back(tempTour);
	}

	int index = 2;
	newTours.at(0) = elite1; 
	newTours.at(1) = elite2;

	do
	{
		tempTour = this->Mutate(oldTours.at(0).GetTourPath(),tempTour);
		newTours.at(index) = tempTour;
		index++;
	}
	while(index != numOfMutations + 2);

	do
	{
		std::next_permutation(this->currentTourGA.GetTourPath(),this->currentTourGA.GetTourPath()+this->numOfCities);
		newTours.at(index) = this->currentTourGA;
		index++;
	}
	while(index != numTours);
	
	return newTours;
}

void Simulation::SetCurrentTourGA()
{
	this->currentTourGA.SetNumCities(this->numOfCities);
	for(int i = 0; i < this->numOfCities; i++)
	{
		this->currentTourGA.SetCityLocation(i,i);
	}
}

void Simulation::GeneticAlgorithm()
{
	
	this->SetCurrentTourGA();

	Tour eliteTour1;
	eliteTour1.SetNumCities(this->numOfCities);
	double eliteTourValue1 = 900000.0;
	Tour eliteTour2;
	eliteTour2.SetNumCities(this->numOfCities);
	double eliteTourValue2 = 900000.0;
	
	//Time start point
	auto startTime = std::chrono::high_resolution_clock::now();

	//Start Algorithm

	std::vector<Tour> tours;
	Tour t;
	t.SetNumCities(this->numOfCities);
	for(int i = 0; i < this->numTours; i++)
	{
		tours.push_back(t);
	}
	tours.at(0) = this->currentTourGA;
	for(int i = 1; i < this->numTours; i++)
	{
		std::next_permutation(this->currentTourGA.GetTourPath(),this->currentTourGA.GetTourPath()+this->numOfCities);
		tours.at(i) = this->currentTourGA;
	}

	for(int i = 0; i < this->numTours; i++)
	{	
		if(tours.at(i).GetTourValue(this->numOfCities,this->cities) < eliteTourValue1)
		{
			eliteTourValue2 = eliteTourValue1;
			eliteTourValue1 = tours.at(i).GetTourValue(numOfCities,this->cities);
			eliteTour1 = this->currentTourGA;
		}
		else
		{
			if(tours.at(i).GetTourValue(this->numOfCities,this->cities) < eliteTourValue2)
			{
				eliteTourValue2 = tours.at(i).GetTourValue(this->numOfCities,this->cities);
				eliteTour2 = this->currentTourGA;
			}
		}
	}

	//Repeat Generations
	double dnumOfMutations = double(percent) / 100.0;
	int numOfMutations = dnumOfMutations * numTours;
	
	for(int i = 1; i < this->numGenerations; i++)
	{
		tours = this->MakeNextGeneration(numOfMutations,tours,eliteTour1,eliteTour2);
		for(int j = 0; j < this->numTours; j++)
		{
			if(tours.at(j).GetTourValue(this->numOfCities,this->cities) < eliteTourValue1)
			{
				eliteTourValue2 = eliteTourValue1;
				eliteTourValue1 = tours.at(j).GetTourValue(this->numOfCities,this->cities);
				eliteTour1 = this->currentTourGA;	
			}
			else
			{
				if(tours.at(j).GetTourValue(this->numOfCities,this->cities) < eliteTourValue2)
				{
					eliteTourValue2 = tours.at(i).GetTourValue(this->numOfCities,this->cities);
					eliteTour2 = this->currentTourGA;
				}
			}
		}
	}
	
	this->algorithmCost = eliteTourValue1;

	//Time end point
	auto endTime = std::chrono::high_resolution_clock::now();
	auto durationSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
	
	//ConvertTotaltime to an integer, represented as seconds
	this->algorithmTimeInSec = std::chrono::duration<double>(durationSeconds).count();
}

void Simulation::PrintSimulationResults()
{
	std::cout << "The number of cities computed is " << this->numOfCities << std::endl;
	std::cout << "The cost of the brute force algorithm is " << this->bruteForceCost << std::endl;
	std::cout << "The time the brute force algorithm took is " << this->bruteForceTimeInSec << " seconds" <<  std::endl;
	std::cout << "The cost of the genetic algoirthm is " << this->algorithmCost << std::endl;
	std::cout << "The time the genetic algorithm took is " << this->algorithmTimeInSec << " seconds" << std::endl;
	std::cout << "In this execution the genetic algoirthm was " <<  (this->algorithmCost/this->bruteForceCost) * 100.0 << "%" << " optimal" << std::endl;

}