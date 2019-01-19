// PEA-PWR-proj3.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <chrono>
#include <conio.h>
#include "GeneticAlgorithm.h"

string dataFolder = "testData/";
string symFolder = "SYM/";
string asyFolder = "ASY/";
const int dataRangesCount = 7;
const int dataRangesSYM[dataRangesCount] = { 17, 48, 52, 76, 96, 136, 150 };
const string dataRangesPrefixesSYM[dataRangesCount] = { "gr", "gr", "berlin", "pr", "gr", "pr", "ch" };
const int dataRangesASY[dataRangesCount] = { 17, 33, 47, 64, 70, 170, 323 };
const string dataRangesPrefixesASY[dataRangesCount] = { "br", "ftv", "ftv", "ftv", "ftv", "ftv", "rbg" };

int main()
{
	GeneticAlgorithm testGA;
	int testData = 0;
	testGA.setSource(dataFolder + symFolder + dataRangesPrefixesSYM[testData] + to_string(dataRangesSYM[testData]) + ".txt");
    //std::cout << testGA.printSource();
	testGA.solve(10, 5);
}

