#include "stdafx.h"
#include "TSP.h"
#include "Node.h"
#include <queue>
using namespace std;

TSP::TSP()
{
	cin >> numberOFcities;
	costMatrix = new int*[numberOFcities];
	for (int i = 0; i < numberOFcities; i++)
	{
		costMatrix[i] = new int[numberOFcities];
		for (int j = 0; j < numberOFcities; j++)
			cin >> costMatrix[i][j];
	}
}

TSP::TSP(int size)
{
	srand(time(NULL));
	numberOFcities = size;
	costMatrix = new int*[numberOFcities];
	for (int i = 0; i < numberOFcities; i++)
	{
		costMatrix[i] = new int[numberOFcities];
		for (int j = 0; j < numberOFcities; j++)
		{
			if (i == j)
			{
				costMatrix[i][j] = -1;
			}
			else
			{
				costMatrix[i][j] = rand() % 100;
			}
		}
	}
}

TSP::TSP(string name)
{
	fstream plik;
	plik.open(name, ios::in);
	if (plik.good())
	{
		plik >> numberOFcities;
		costMatrix = new int*[numberOFcities];
		for (int i = 0; i < numberOFcities; i++)
		{
			costMatrix[i] = new int[numberOFcities];
			for (int j = 0; j < numberOFcities; j++)
				plik >> costMatrix[i][j];
		}
	}
	else
		cout << "Bledna nazwa pliku!" << endl;
	plik.close();
}



TSP::~TSP()
{
	for (int i = 0; i < numberOFcities; i++)
		delete[] costMatrix[i];
	delete[] costMatrix;
}




void TSP::print()
{
	for (int i = 0; i < numberOFcities; i++)
		cout << setw(3) << " " << i;
	cout << endl;
	for (int i = 0; i < numberOFcities; i++)
	{
		cout << i << " ";
		for (int j = 0; j < numberOFcities; j++)
			cout << setw(3) << costMatrix[i][j] << " ";
		cout << endl;
	}
}
class cmpLowerBound
{
public:
	bool operator() (const Node *node1, const Node *node2)
	{
		if (node1->lowerBound > node2->lowerBound) return true;
		else return false;
	}
};
void TSP::BB()
{
	priority_queue <Node*, vector<Node*>, cmpLowerBound> kolejka;
	Node *n = new Node(costMatrix, numberOFcities, NULL, 0);
	kolejka.push(n);
	
	int minCost = INT_MAX;
	endNode = NULL;
	while (!kolejka.empty())
	{
		Node * n = kolejka.top();
		kolejka.pop();

		if (n->endPath())
		{
			if (minCost > n->lowerBound)
			{
				endNode = n;
				minCost = n->lowerBound;
			}
			continue;
		}
		if (n->lowerBound > minCost)
		{
			continue;
		}
		vector<Node*>* children = n->generateChildren();
		for (auto it = children->begin(); it != children->end(); it++)
		{
			kolejka.push(*it);
		}
		children->clear();
		children->shrink_to_fit();
		
	}
}

void TSP::printResult()
{
	cout << "Rozwiazanie: \n" << endNode->lowerBound << endl;
	cout << "Path: ";
	for (auto it = endNode->path.begin(); it != endNode->path.end(); it++)
	{
		cout << *it << "-> ";
	}
	cout << endNode->path.at(0) << endl;
}

