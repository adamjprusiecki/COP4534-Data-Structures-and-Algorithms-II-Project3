#ifndef SIMULATION_HPP_
#define SIMULATION_HPP_

#include "City.hpp"
#include "Tour.hpp"
#include <vector>

class Simulation
{
	private:
		City cities[20];
		Tour currentTourGA;
		int numOfCities = 0;
		int numTours = 0;
		int numGenerations = 0;
		int percent = 0;
		double bruteForceCost = 0.0;
		double bruteForceTimeInSec = 0.0;
		double algorithmCost = 0.0;
		double algorithmTimeInSec = 0.0;

		void GenerateCities();
		unsigned long int GetFactorial(int num);
		Tour Mutate(int tourPath[],Tour tempTour);
		std::vector<Tour> MakeNextGeneration(int numOfMutations,std::vector<Tour> oldTour,Tour elite1,Tour elite2);
		void SetCurrentTourGA();

	public:
		Simulation(int numOfCities,int numTours,int numGenerations, int percent);
		void BruteForce();
		void GeneticAlgorithm();
		void PrintSimulationResults();
};

#endif // SIMULATION_HPP_