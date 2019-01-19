#include "pch.h"
#include "GeneticAlgorithm.h"

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
void GeneticAlgorithm::solve()
{
}
