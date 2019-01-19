#include "pch.h"
#include "AdjacencyMatrix.h"


AdjacencyMatrix::AdjacencyMatrix(){
}


AdjacencyMatrix::~AdjacencyMatrix(){
	deleteMatrix();
}

void AdjacencyMatrix::createMatrix() { // Creates empty matrix
	matrixPtr = new int *[n];
	for (int i = 0; i < n; i++) {
		matrixPtr[i] = new int[n];
		for (int j = 0; j < n; j++) {
			matrixPtr[i][j] = INT_MAX; // Treating maximum value of int as nonexistent edge
		}
	}
}

void AdjacencyMatrix::deleteMatrix() {
	if (matrixPtr != nullptr) {
		for (int i = 0; i < n; i++) {
			delete[] matrixPtr[i];
		}
		delete[] matrixPtr;
		matrixPtr = nullptr;
	}
}

int AdjacencyMatrix::generateFromFile(string filename) 
{
	deleteMatrix();
	ifstream input(filename.c_str());
	if (!input) {
		return 0;
	}
	input >> n; // reading nodes count

	createMatrix();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int temp;
			input >> temp;
			matrixPtr[i][j] = temp;
			if (i == j) matrixPtr[i][j] = INT_MAX;
		}
	}

	input.close();
	return 1;
}

string AdjacencyMatrix::printStruct() {
	if (matrixPtr == nullptr) {
		return "Graph is empty!\n";
	}
	string structure = "Adjacency Matrix:\n\\";
	for (int i = 0; i < n; i++) {
		structure += ' ' + to_string(i);
	}

	structure += '\n';

	for (int i = 0; i < n; i++) {
		structure += to_string(i);
		for (int j = 0; j < n; j++) {
			if (matrixPtr[i][j] == INT_MAX) {
				structure += " x";
			}
			else {
				structure += ' ' + to_string(matrixPtr[i][j]);
			}
		}
		structure += '\n';
	}

	return structure;
}

int AdjacencyMatrix::getNodesNumber()
{
	return n;
}

int AdjacencyMatrix::getElement(int n, int m)
{
	return matrixPtr[n][m];
}

int ** AdjacencyMatrix::getMatrixPtr()
{
	return matrixPtr;
}

bool AdjacencyMatrix::isEmpty()
{
	if (matrixPtr == nullptr) {
		return true;
	}
	else {
		return false;
	}
}
