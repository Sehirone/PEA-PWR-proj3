#pragma once
#include "AdjacencyMatrix.h"

class GeneticAlgorithm
{
private:
	AdjacencyMatrix cities;
	int* shortestRoute = nullptr;
	int shortestRouteValue = INT_MAX;
	int** population = nullptr;
	int startingNode = 0;

	int calculateRouteLength(int * route);
	void setRandomRoute(int * route);

public:
	GeneticAlgorithm();
	~GeneticAlgorithm();

	int setSource(string filename);
	string printSource();

	void solve(int populationSize);
};

