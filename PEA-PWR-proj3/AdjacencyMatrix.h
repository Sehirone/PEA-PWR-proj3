#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#ifndef TO_STRING
#define TO_STRING
template<class s>
string to_string(s data) {
    stringstream ss;
    ss << data;
    return ss.str();
}
#endif

class AdjacencyMatrix{
    private:
        int n; // number of nodes
        int **matrixPtr = nullptr;

		void createMatrix(); // Creates empty matrix
		void deleteMatrix();

    public:
		AdjacencyMatrix();
		~AdjacencyMatrix();
		int generateFromFile(string filename);
		string printStruct();
		int getNodesNumber();
		int getElement(int n, int m);
		int** getMatrixPtr();
		bool isEmpty();
};
