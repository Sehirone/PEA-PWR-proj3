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

	delete[] alreadyVisited;
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
// Copies one population into another based on selected parents
// *********************************************************************************************
void GeneticAlgorithm::copyPopulation(int ** from, int ** to, int * selectedParents, int populationSize)

{
	for (int j = 0; j < populationSize; j++) {
		for (int i = 0; i < cities.getNodesNumber(); i++) {
			to[j][i] = from[selectedParents[j]][i];
		}
	}
}

// *********************************************************************************************
// Copies one population into another intact
// *********************************************************************************************
void GeneticAlgorithm::copyPopulationIntact(int ** from, int ** to, int populationSize)

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
// Mutates given route by swapping two diffrent points
// *********************************************************************************************
void GeneticAlgorithm::mutate(int * route)
{
	int pointA = 0;
	int pointB = 0;
	std::uniform_int_distribution<std::mt19937::result_type> popDist(0, cities.getNodesNumber() - 1);
	while (pointA == pointB) {
		pointA = popDist(rng);
		pointB = popDist(rng);
	}
	swapElements(route, pointA, pointB);
}

// *********************************************************************************************
// Swaps two elements in an array
// *********************************************************************************************
void GeneticAlgorithm::swapElements(int * route, int i, int j)
{
	int temp = route[i];
	route[i] = route[j];
	route[j] = temp;
}

// *********************************************************************************************
// Crosses two populations w/ one crossing point - PMX: Partially - Mapped Crossover
// *********************************************************************************************
void GeneticAlgorithm::crossOnePoint(int * routeA, int * routeB)
{
	// Create temp routes
	int *tempRouteA = new int[cities.getNodesNumber()];
	int *tempRouteB = new int[cities.getNodesNumber()];
	copyRoute(routeA, tempRouteA);
	copyRoute(routeB, tempRouteB);

	// Generate crossing point
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, (cities.getNodesNumber() - 1));
	int crossingPoint = dist(rng);

	// Cross that based on PMX - Partially - Mapped Crossover
	for (int i = 0; i < crossingPoint; i++) {
		int position = findInArray(routeA, tempRouteB[i]);
		routeA[position] = routeA[i];
		routeA[i] = tempRouteB[i];
	}
	for (int i = 0; i < crossingPoint; i++) {
		int position = findInArray(routeB, tempRouteA[i]);
		routeB[position] = routeB[i];
		routeB[i] = tempRouteA[i];
	}

	delete[] tempRouteA;
	delete[] tempRouteB;
}

// *********************************************************************************************
// Find given number in an array - return its position
// *********************************************************************************************
int GeneticAlgorithm::findInArray(int * array, int number)
{
	for (int i = 0; i < cities.getNodesNumber(); i++) {
		if (array[i] == number) {
			return i;
		}
	}
	return -1;
}

// *********************************************************************************************
// Copies one route into another
// *********************************************************************************************
void GeneticAlgorithm::copyRoute(int * from, int * to)
{
	for (int i = 0; i < cities.getNodesNumber(); i++) {
		to[i] = from[i];
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
// Destructor - clears shortest route
// *********************************************************************************************
GeneticAlgorithm::~GeneticAlgorithm()
{
	if (shortestRoute != nullptr) {
		delete[] shortestRoute;
	}
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
// Prints stored shortest route
// *********************************************************************************************
string GeneticAlgorithm::getShortestRoute()
{
	if (cities.isEmpty() || shortestRoute == nullptr) {
		return "No graph to solve!";
	}
	string temp = "";
	for (int i = 0; i < cities.getNodesNumber(); i++) {
		temp += to_string(shortestRoute[i]) + " -> ";
	}
	temp += to_string(shortestRoute[0]);
	return temp;
}

// *********************************************************************************************
// Getter for shortestRouteValue
// *********************************************************************************************
int GeneticAlgorithm::getShortestRouteValue()
{
	return shortestRouteValue == INT_MAX ? 0 : shortestRouteValue;
}

// *********************************************************************************************
// Where the Magic takes place, solves TSP using genetic algorithm
// Selection modes: 1 - Grades proportionate selection
//					2 - Tournament selection - TO DO
// *********************************************************************************************
void GeneticAlgorithm::solve(const int populationSize, const double crossProb, const double mutProb, int iterations, const int selectionMode)
{
	if (cities.isEmpty() || populationSize % 2 == 1) {
		return;
	}
	// Init shortestroute/shortestroutevalue using greedy aproach
	initRoute();

	if (iterations == -1) {
		iterations = cities.getNodesNumber() * cities.getNodesNumber() * 2;
	}

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
	int * selectedParents = new int[populationSize];

	// Init grades
	int* grades = new int[populationSize];
	for (int j = 0; j < populationSize; j++) {
		grades[j] = gradeRoute(population[j]);
	}
	normalizeGrades(grades, populationSize);

	// set current best solution as best
	int bestGrade = INT_MAX * (-1);
	int bestFromPop;
	for (int i = 0; i < populationSize; i++) {
		if (grades[i] > bestGrade) {
			bestGrade = grades[i];
			bestFromPop = i;
		}
	}
	copyRoute(population[bestFromPop], shortestRoute);
	shortestRouteValue = calculateRouteLength(population[bestFromPop]);

	// Distribution for crossing/mutation prob
	std::uniform_real_distribution<double> happeningProb(0.0, 1.0);

	// **********
	// Main magic
	// **********
	for (int i = 0; i < iterations; i++) {
		// Selecting parents
		switch (selectionMode) {
		case 1:
			selectByRoullete(grades, selectedParents, populationSize);
			break;
		case 2:
			break;
		}

		// Create new population based on selected parents
		copyPopulation(population, newPopulation, selectedParents, populationSize);

		// Crossing first / Mutating later
		for (int j = 0; j < populationSize/2; j++) {
			if (happeningProb(rng) <= crossProb) {
				crossOnePoint(newPopulation[j * 2], newPopulation[(j * 2) + 1]);
			}
		}
		for (int j = 0; j < populationSize; j++) {
			if (happeningProb(rng) <= mutProb) {
				mutate(newPopulation[j]);
			}
		}

		// Grading new population
		for (int j = 0; j < populationSize; j++) {
			grades[j] = gradeRoute(newPopulation[j]);
		}
		normalizeGrades(grades, populationSize);

		// Copy new population into population
		copyPopulationIntact(newPopulation, population, populationSize);
		
		// set new best solution if found
		bestGrade = INT_MAX * (-1);
		bestFromPop;
		for (int j = 0; j < populationSize; j++) {
			if (grades[j] > bestGrade) {
				bestGrade = grades[j];
				bestFromPop = j;
			}
		}
		if (calculateRouteLength(population[bestFromPop]) < shortestRouteValue) {
			copyRoute(population[bestFromPop], shortestRoute);
			shortestRouteValue = calculateRouteLength(population[bestFromPop]);
			cout << "iteration: " << i << " length: " << shortestRouteValue << endl;
		}
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
