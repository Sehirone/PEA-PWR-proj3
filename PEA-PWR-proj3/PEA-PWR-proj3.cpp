// PEA-PWR-proj3.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <chrono>
#include <conio.h>
#include "GeneticAlgorithm.h"

void displayMenu() {
	std::cout << "TSP:" << endl;
	std::cout << "1.Wczytaj z pliku" << endl;
	std::cout << "2.Solve Genetic Algorithm" << endl;
	std::cout << "4.Print struct" << endl;
	std::cout << "7.Test (pomiary)" << endl;
	std::cout << "0.Exit" << endl;
	std::cout << "Podaj opcje:";
}

void waitForConfirmation() {
	std::cout << "Press any key to continue" << endl;
	cin.clear();
	cin.ignore(256, '\n');
	_getche();
}

string dataFolder = "testData/";
string symFolder = "SYM/";
string asyFolder = "ASY/";
ofstream testOutput;
string testFileOutput = dataFolder + "testsData.txt";
const int dataRangesCount = 4;
const int dataRangesSYM[dataRangesCount] = { 17, 48, 96, 136 };
const string dataRangesPrefixesSYM[dataRangesCount] = { "gr", "gr", "gr", "pr" };
const int dataRangesASY[dataRangesCount] = { 17, 47, 70, 170 };
const string dataRangesPrefixesASY[dataRangesCount] = { "br", "ftv", "ftv", "ftv"};
const int mutationChancesCount = 4;
const double mutationChances[mutationChancesCount] = { 0.01, 0.05, 0.1, 0.15};
const int crossChancesCount = 6;
const double crossChances[crossChancesCount] = { 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };
const int populationSizeCount = 4;
const int populationSize[populationSizeCount] = { 10, 30, 50, 70};
const int testsCount = 20;

int main() {
	char opt;
	string filename;
	GeneticAlgorithm testGA;

	while (true) {
		system("cls");
		displayMenu();
		opt = _getche();
		system("cls");
		switch (opt)
		{
		case '1':
			std::cout << "Nazwa pliku: ";
			cin >> filename;
			if (!testGA.setSource(dataFolder + filename)) {
				std::cout << "Wczytywanie nie powiodlo sie!" << endl;
				waitForConfirmation();
				break;
			}
			std::cout << "Wczytano dane pomyslnie!" << endl;
			waitForConfirmation();
			break;
		case '2':
			int pop, iter;
			double crossCh, mutCh;
			cout << "Population: ";
			cin >> pop;
			cout << "Iterations: ";
			cin >> iter;
			cout << "Cross chance: ";
			cin >> crossCh;
			cout << "Mutation chance: ";
			cin >> mutCh;
			testGA.solve(pop, crossCh, mutCh, iter);
			std::cout << testGA.getShortestRoute() << endl;
			std::cout << to_string(testGA.getShortestRouteValue()) << endl;
			waitForConfirmation();
			break;
		case '4':
			std::cout << testGA.printSource() << endl;
			waitForConfirmation();
			break;
		case '7':
			testOutput.open(testFileOutput);
			if (!testOutput) {
				std::cout << "BLAD otwarcia pliku zapisu testow!";
				waitForConfirmation();
				break;
			}

			testOutput << "Czasy podano w microsekukndach" << endl;

			testOutput << "GA Symmetric" << endl;
			testOutput << "L.miast\tRozwiazanie\tPopulacja\tMutacja%\tKrzyzowanie%" << endl;
			for (int i = 0; i < dataRangesCount; i++) {
				testGA.setSource(dataFolder + "SYM/" + dataRangesPrefixesSYM[i] + to_string(dataRangesSYM[i]) + ".txt");
				for (int a = 0; a < populationSizeCount; a++) {
					for (int b = 0; b < mutationChancesCount; b++) {
						for (int c = 0; c < crossChancesCount; c++) {
							int result = 0;
							//auto startTime = chrono::high_resolution_clock::now();
							for (int j = 0; j < testsCount; j++) {
								testGA.solve(populationSize[a], crossChances[c], mutationChances[b]);
								result += testGA.getShortestRouteValue();
							}
							//auto finishTime = chrono::high_resolution_clock::now();
							//auto operationTime = chrono::duration_cast<chrono::microseconds>(finishTime - startTime).count() / testsCount;
							testOutput << to_string(dataRangesSYM[i]) << '\t' << to_string(result / testsCount) << '\t' << to_string(populationSize[a]) << '\t' << to_string(mutationChances[b]) << '\t' << to_string(crossChances[c]) << '\t' << endl;
							testOutput.flush();
						}
					}
				}
			}
			testOutput << endl;

			testOutput << "GA Asymmetric" << endl;
			testOutput << "L.miast\tRozwiazanie\tPopulacja\tMutacja%\tKrzyzowanie%" << endl;
			for (int i = 0; i < dataRangesCount; i++) {
				testGA.setSource(dataFolder + "ASY/" + dataRangesPrefixesASY[i] + to_string(dataRangesASY[i]) + ".txt");
				for (int a = 0; a < populationSizeCount; a++) {
					for (int b = 0; b < mutationChancesCount; b++) {
						for (int c = 0; c < crossChancesCount; c++) {
							int result = 0;
							//auto startTime = chrono::high_resolution_clock::now();
							for (int j = 0; j < testsCount; j++) {
								testGA.solve(populationSize[a], crossChances[c], mutationChances[b]);
								result += testGA.getShortestRouteValue();
							}
							//auto finishTime = chrono::high_resolution_clock::now();
							//auto operationTime = chrono::duration_cast<chrono::microseconds>(finishTime - startTime).count() / testsCount;
							testOutput << to_string(dataRangesSYM[i]) << '\t' << to_string(result / testsCount) << '\t' << to_string(populationSize[a]) << '\t' << to_string(mutationChances[b]) << '\t' << to_string(crossChances[c]) << '\t' << endl;
							testOutput.flush();
						}
					}
				}
			}
			testOutput << endl;

			testOutput.close();
			waitForConfirmation();
			break;
		case '0':
			return 0;
		default:
			break;
		}
	}
}

