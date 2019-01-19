#include "pch.h"
#include "GeneticAlgorithm.h"
#include <vector>
#include <random>


// *********************************************************************************************
// Initializes shortestRoute and shortestRouteValue using greedy aproach treating startNode as 0
// *********************************************************************************************
void GeneticAlgorithm::initRoute()
{
	if (shortestRoute != nullptr) {
		delete shortestRoute;
	}
	shortestRoute = new int[cities.getNodesNumber()];
	shortestRoute[0] = startingNode;

	bool* alreadyVisited = new bool[cities.getNodesNumber()];
	for (int i = 0; i < cities.getNodesNumber(); i++) {
		alreadyVisited[i] = false;
	}
	alreadyVisited[startingNode] = true;

	for (int i = 0; i < cities.getNodesNumber() - 1; i++) {
		int min = INT_MAX;
		int chosen = -1;
		for (int j = 0; j < cities.getNodesNumber(); j++) {
			if (cities.getElement(shortestRoute[i], j) < min && !alreadyVisited[j]) {
				min = cities.getElement(shortestRoute[i], j);
				chosen = j;
			}
		}
		alreadyVisited[chosen] = true;
		shortestRoute[i + 1] = chosen;
	}

	shortestRouteValue = calculateRouteLength(shortestRoute);
}

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
// Returns grade of a given route -> the higher the better
// *********************************************************************************************
int GeneticAlgorithm::gradeRoute(int * route)
{
	return shortestRouteValue - calculateRouteLength(route);
}

// *********************************************************************************************
// Normalize grades to be greater than zero
// *********************************************************************************************
void GeneticAlgorithm::normalizeGrades(int * grades, int populationSize) {
	int min = 0;
	for (int i = 0; i < populationSize; i++) {
		if (grades[i] < min) {
			min = grades[i];
		}
	}
	min *= -1;
	min++;
	for (int i = 0; i < populationSize; i++) {
		grades[i] += min;
	}
}

// *********************************************************************************************
// Copies one population into another
// *********************************************************************************************
void GeneticAlgorithm::copyPopulation(int ** from, int ** to, int populationSize)
{
	for (int j = 0; j < populationSize; j++) {
		for (int i = 0; i < cities.getNodesNumber(); i++) {
			to[j][i] = from[j][i];
		}
	}
}

// *********************************************************************************************
// Selects parents into selection based on roullete method using grades
// *********************************************************************************************
void GeneticAlgorithm::selectByRoullete(int * grades, int * selection, int populationSize)
{
	int gradesSum = 0;
	int* tempGrades = new int[populationSize];
	for (int i = 0; i < populationSize; i++) {
		gradesSum += grades[i];
		grades[i] = gradesSum;
	}
	std::uniform_int_distribution<std::mt19937::result_type> rulDist(1, gradesSum - 1);

	for (int i = 0; i < populationSize; i++) {
		int selected = rulDist(rng);
		for (int j = 0 ; j < populationSize; j++) {
			if (selected - grades[j] < 0) {
				selection[i] = j;
				break;
			}
		}
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
// Selection modes: 1 - Grades proportionate selection - IN DEVELOPMENT
//					2 - Tournament selection - TO DO
// *********************************************************************************************
void GeneticAlgorithm::solve(const int populationSize, const int iterations, const int selectionMode)
{
	if (cities.isEmpty()) {
		return;
	}
	// Init shortestroute/shortestroutevalue using greedy aproach
	initRoute();

	// Init population
	int** population;
	population = new int*[populationSize];
	for (int i = 0; i < populationSize; i++) {
		population[i] = new int[cities.getNodesNumber()];
		setRandomRoute(population[i]);
	}
	int** newPopulation;
	newPopulation = new int*[populationSize];
	for (int i = 0; i < populationSize; i++) {
		newPopulation[i] = new int[cities.getNodesNumber()];
	}
	copyPopulation(population, newPopulation, populationSize);
	int * selectedParents = new int[populationSize];

	// Init grades
	int* grades = new int[populationSize];
	for (int j = 0; j < populationSize; j++) {
		grades[j] = gradeRoute(population[j]);
	}
	normalizeGrades(grades, populationSize);

	// **********
	// Main magic
	// **********
	for (int i = 0; i < iterations; i++) {
		// Selecting parents pairs
		switch (selectionMode) {
		case 1:
			selectByRoullete(grades, selectedParents, populationSize);
			break;
		case 2:
			break;
		}
		// Crossing / Mutating
		
		
		
		// Grading new population
		for (int j = 0; j < populationSize; j++) {
			grades[j] = gradeRoute(newPopulation[j]);
		}
		normalizeGrades(grades, populationSize);
		for (int j = 0; j < populationSize; j++) { // test
			cout << to_string(grades[j]) << ' ';
		}
		cout << endl; // test
	}


	// Cleanup grades
	delete[] grades;
	// Cleanup population
	for (int i = 0; i < populationSize; i++) {
		delete[] population[i];
	}
	delete[] population;
	for (int i = 0; i < populationSize; i++) {
		delete[] newPopulation[i];
	}
	delete[] newPopulation;
	delete[] selectedParents;
}
