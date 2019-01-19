#include "pch.h"
#include "GeneticAlgorithm.h"
#include <vector>
#include <random>

// *********************************************************************************************
// Calculates length of a given route
// *********************************************************************************************
int GeneticAlgorithm::calculateRouteLength(int * route)
{
	int length = 0;
	for (int i = 0; i < cities.getNodesNumber(); i++) {
		length += cities.getElement(route[i], route[i + 1 >= cities.getNodesNumber() ? 0 : i + 1]);
	}
	return length;
}

// *********************************************************************************************
// Sets random route at given pointer
// *********************************************************************************************
void GeneticAlgorithm::setRandomRoute(int * route) 
{
	std::vector<int> possibleCities;
	for (int i = 0; i < cities.getNodesNumber(); i++) {
		possibleCities.push_back(i);
	}
	possibleCities.erase(possibleCities.begin() + startingNode);
	route[0] = startingNode;

	for (int i = 1; possibleCities.size() > 0; i++) {
		int randomNum = std::uniform_int_distribution<std::mt19937::result_type>{ 0, possibleCities.size() - 1 }(rng);
		route[i] = possibleCities[randomNum];
		possibleCities.erase(possibleCities.begin() + randomNum);
	}
}

// *********************************************************************************************
// Constructor - initializes random number generator
// *********************************************************************************************
GeneticAlgorithm::GeneticAlgorithm()
{
	rng.seed(std::random_device()());
}

// *********************************************************************************************
// Empty destructor
// *********************************************************************************************
GeneticAlgorithm::~GeneticAlgorithm()
{
}

// *********************************************************************************************
// Sets source of adjacencyMatrix containing cities and routes between them
// *********************************************************************************************
int GeneticAlgorithm::setSource(string filename)
{
	return cities.generateFromFile(filename);
}

// *********************************************************************************************
// Prints source of adjacencyMatrix containing cities and routes between them
// *********************************************************************************************
string GeneticAlgorithm::printSource()
{
	return cities.printStruct();
}

// *********************************************************************************************
// Where the Magic takes place, solves TSP using genetic algorithm
// *********************************************************************************************
void GeneticAlgorithm::solve(const int populationSize)
{
	if (cities.isEmpty()) {
		return;
	}

	// Init population
	population = new int*[populationSize];
	for (int i = 0; i < populationSize; i++) {
		population[i] = new int[cities.getNodesNumber()];
		setRandomRoute(population[i]);
	}




	// Cleanup population
	for (int i = 0; i < populationSize; i++) {
		delete[] population[i];
	}
	delete[] population;
	population = nullptr;
}
