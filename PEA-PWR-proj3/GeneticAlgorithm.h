#pragma once
#include "AdjacencyMatrix.h"

class GeneticAlgorithm
{
private:
	AdjacencyMatrix cities;

public:
	GeneticAlgorithm();
	~GeneticAlgorithm();

	int setSource(string filename);
	string printSource();

	void solve();
};

