#include "Driver.hpp"
#include "Simulation.hpp"
#include <iostream>

Driver::Driver()
{

}

void Driver::Run()
{
	this->GetUserInput();
	Simulation s(this->numCities,this->numTours,this->numGenerations,this->percent);
	s.BruteForce();
	s.GeneticAlgorithm();
	s.PrintSimulationResults();
}

void Driver::GetUserInput()
{
	/*
	int lnumCities;
	int lnumTours;
	int lnumGenerations;
	int lpercent;

	std::cout << "How many cities are there?: ";
	std::cin >> lnumCities;
	std::cout << "How many individual tours are there in a generation?: ";
	std::cin >> lnumTours;
	std::cout << "How many generations are there?: ";
	std::cin >> lnumGenerations;
	std::cout << "What percentage of a generation should be comprised of mutations?: ";
	std::cin >> lpercent;
	std::cout << std::endl;

	this->numCities = lnumCities;
	this->numTours = lnumTours;
	this->numGenerations = lnumGenerations;
	this->percent = lpercent;
*/

	//The values i tested with to get the results for my excel file
	this->numCities = 11;
	this->numTours = 4000;
	this->numGenerations = 200;
	this->percent = 75;
}
