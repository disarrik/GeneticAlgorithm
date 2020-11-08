#include "Population.h"
#include <vector>
#include <iostream>
#include <ctime>

using namespace std;

int fitness(vector<vector<int>> genom) {
	int count = 0;
	for (unsigned int i = 0; i < genom.size(); i++)
	{
		for (unsigned int j = 0; j < genom[i].size(); j++)
		{
			count += genom[i][j];
		}
	}
	return count;
}

int main() {
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	Population population(30, 5, 9, 9, 1, fitness);
	population.NextGeneration(800);
	population.showBest();
}