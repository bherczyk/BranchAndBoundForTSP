#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "Node.h"


class TSP
{
private:

	int numberOFcities;
	int **costMatrix;
	Node* endNode;

public:

	TSP();
	TSP(std::string);
	TSP(int size);

	void print();
	void printResult();

	void BB();

	~TSP();
};

