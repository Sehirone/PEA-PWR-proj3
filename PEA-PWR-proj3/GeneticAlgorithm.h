#pragma once
#include "AdjacencyMatrix.h"
#include <random>

class GeneticAlgorithm
{
private:
	AdjacencyMatrix cities;
	int* shortestRoute = nullptr;
	int shortestRouteValue = INT_MAX;
	int startingNode = 0;
	mt19937 rng;

	void initRoute();
	int calculateRouteLength(int * route);
	void setRandomRoute(int * route);
	int gradeRoute(int * route);
	void normalizeGrades(int * grades, int populationSize);
	void copyPopulation(int** from, int** to, int * selectedParents, int populationSize);
	void copyPopulationIntact(int ** from, int ** to, int populationSize);
	void selectByRoullete(int * grades, int * selection, int populationSize);
	void mutate(int * route, int populationSize);
	void swapElements(int * route, int i, int j);
	void crossOnePoint(int * routeA, int * routeB);
	bool isOnList(vector<int> list, int number);
	void copyRoute(int * from, int * to);

public:
	GeneticAlgorithm();
	~GeneticAlgorithm();

	int setSource(string filename);
	string printSource();
	string getShortestRoute();
	int getShortestRouteValue();

	void solve(const int populationSize, const double crossProb, const double mutProb, int iterations = -1, const int selectionMode = 1);
};

