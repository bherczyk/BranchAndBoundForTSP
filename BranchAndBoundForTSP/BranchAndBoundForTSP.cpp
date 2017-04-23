// Cw1.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
#include "TSP.h"
#include <Windows.h>


void menu();
LARGE_INTEGER startTimer()
{
	LARGE_INTEGER start;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&start);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return start;
}
LARGE_INTEGER endTimer()
{
	LARGE_INTEGER stop;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&stop);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return stop;
}

int _tmain(int argc, _TCHAR* argv[])
{
	menu();
	return 0;
}

void menu() {
	using namespace std;

	TSP *T;
	T = NULL;
	int choice;
	do
	{
		system("cls");
		cout << "1. Wczytaj dane i wyswietl." << endl;
		cout << "2. Algorytm" << endl;
		cout << "3. Losuj dane i wyswietl" << endl;
		cout << "4. Czas" << endl;
		cout << "0. Koniec" << endl;

		cin >> choice;
		switch (choice)
		{
		case 1:
		{
				  system("cls");
				  cout << "Podaj nazwe pliku" << endl;
				  string name;
				  cin >> name;
				  T = new TSP(name);
				  T->print();
				  cin.ignore();
				  cin.get();
				  break;
		}
		case 2:
		{
				  T->BB();
				  T->printResult();
				  cin.get();
				  cin.get();
				  break;
		}
		case 3:
		{
				  system("cls");
				  cout << " Podaj liczbe miast" << endl;
				  
				  int cities;
				  cin >> cities;

				  T = new TSP(cities);
				  T->print();
				  cin.ignore();
				  cin.get();
				  break;
		}
		case 4:
		{
				  LARGE_INTEGER performanceCountStart, performanceCountEnd;
				  unsigned _int64 freq;
				  QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&freq));
				  system("cls");

	
				  performanceCountStart = startTimer();
				  T->BB();
				  performanceCountEnd = endTimer();
				  double tm = (performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / (double)freq * 1000;
				  cout << " Czas = " << tm << "[ms]" << endl;
				  cin.ignore();
				  cin.get();
				  break;
		}
		default:
			break;
		}
	} while (choice);
}

