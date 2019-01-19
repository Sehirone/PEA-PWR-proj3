#include "pch.h"
#include "GeneticAlgorithm.h"
#include <vector>

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
	for()
}

// *********************************************************************************************
// Empty constructor
// *********************************************************************************************
GeneticAlgorithm::GeneticAlgorithm()
{
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

	// Init 
	population = new int*[populationSize];
	for (int i = 0; i < populationSize; i++) {
		population[i] = new int[cities.getNodesNumber()];
	}




	// Cleanup
	for (int i = 0; i < populationSize; i++) {
		delete[] population[i];
	}
	delete[] population;
	population = nullptr;
}
