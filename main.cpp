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
	srand((int) time(0));
	setlocale(LC_ALL, "Russian");
	Population population(4, 5, 3, 7, 0, fitness);
	population.show();
	cout << "-------------------" << endl;
	population.NextGeneration(1);
	population.show();
}