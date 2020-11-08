#include "Population.h"
#include <vector>

using namespace std;

int fitness(vector<vector<int>> genom) {
	int count = 0;
	for (int i = 0; i < genom.size(); i++)
	{
		for (int j = 0; j < genom[i].size(); j++)
		{
			count += genom[i][j];
		}
	}
	return count;
}

int main() {
	Population population(10, 5, 3, 7, 20, fitness);
	population.NextGeneration(10);
	population.show();
}