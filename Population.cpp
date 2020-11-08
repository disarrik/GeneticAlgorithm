#include "Population.h"
#include <vector>
#include <ctime>
#include <iostream>

using namespace std;


//---------------------------------определение класса Population с прототипами----------------------------
class Population
{
	class Specie;
	int speciesAmount;
	int refreshingAmount;
	int chromosomesAmount;
	int genesAmount;
	int mutationChance;
	int (*fitness)();
	vector<Specie*> allSpecies;
	void sort();
public:
	Population(int speciesAmount, int refreshingAmount, int сhromosomesAmount, int genesAmount, int mutationChance, int (*fitness)());
	void NextGeneration(int steps = 0);
	void show();
	void showBest();
};


//-------------------------определение класса Species, вложенного в Population--------------------------------
class Population::Specie {
	int chromosomesAmount;
	int genesAmount;
	int mutationChance;
	vector<vector<int>> chromosomes; //двумерный односвязанный список[хромосома][ген]
public:
	int (*fitness)();
	Specie(int chromosomesAmount, int genesAmount, int mutationChance, int (*fitness)());
	void show();
	Specie crossingover(Specie second);
};


//------------------------определение методов класса Species, вложенного в Population--------------------------
Population::Specie::Specie(int chromosomesAmount, int genesAmount, int mutationChance, int (*fitness)()) {
	this->chromosomesAmount = chromosomesAmount;
	this->genesAmount = genesAmount;
	this->fitness = fitness;
	this->mutationChance = mutationChance;
	srand(time(0));
	chromosomes.resize(chromosomesAmount);
	for (int i = 0; i < chromosomesAmount; i++)
	{
		chromosomes[i].resize(genesAmount);
		for (int j = 0; j < genesAmount; j++)
		{
			chromosomes[i][j] = rand() % 2;
		}
	}
}

void Population::Specie::show() {
	for (int i = 0; i < chromosomes.size(); i++)
	{
		for (int j = 0; j < chromosomes[i].size(); j++)
		{
			cout << chromosomes[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

Population::Specie Population::Specie::crossingover(Specie second) {
	Specie child(this->chromosomesAmount, this->genesAmount, this->mutationChance, fitness);
	srand(time(0));
	for (int i = 0; i < chromosomesAmount; i++)
	{
		int border = rand() % (genesAmount + 1);
		for (int j = 0; j < genesAmount - border; j++)
		{
			child.chromosomes[i][j] = second.chromosomes[i][j];
			int reverse = child.chromosomes[i][j] == 0 ? 1 : 0;
			child.chromosomes[i][j] = rand() % 100 > mutationChance ? child.chromosomes[i][j] : reverse;
		}
		for (int j = genesAmount - border; j < border; j++)
		{
			child.chromosomes[i][j] =  this->chromosomes[i][j];
			int reverse = child.chromosomes[i][j] == 0 ? 1 : 0;
			child.chromosomes[i][j] = rand() % 100 > mutationChance ? child.chromosomes[i][j] : reverse;
		}
	}
	return child;
}


//------------------------определение методов класса Population--------------------------
Population::Population(int speciesAmount, int refreshingAmount, int сhromosomesAmount, int genesAmount, int mutationChance, int (*fitness)()) {
	this->speciesAmount = speciesAmount;
	this->chromosomesAmount = сhromosomesAmount;
	this->genesAmount = genesAmount;
	this->fitness = fitness;
	allSpecies.resize(speciesAmount);
	for (int i = 0; i < speciesAmount; i++)
	{
		allSpecies[i] = new Specie(chromosomesAmount, genesAmount, mutationChance, fitness);
	}
}

void Population::sort() {
	for (int i = 0; i < allSpecies.size(); i++)
	{
		for (int j = 0; j < allSpecies.size() - i - 1; j++)
		{
			if (allSpecies[j]->fitness() > allSpecies[j+1]->fitness()) {
				Specie* a = allSpecies[j];
				allSpecies[j] = allSpecies[j + 1];
				allSpecies[j + 1] = a;
			}
		}
	}
}

void Population::show() {
	for (int i = 0; i < speciesAmount; i++)
	{
		allSpecies[i]->show();
		cout << endl;
	}
}

void Population::NextGeneration(int steps = 1) {
	for (int i = 0; i < steps; i++)
	{
		sort();
		for (int i = 0; i < speciesAmount / 2; i++)
		{
			delete allSpecies[i];
			allSpecies[i] = new Specie(chromosomesAmount, genesAmount, mutationChance, fitness);
			*allSpecies[i] = allSpecies[rand() % (speciesAmount - 1) - speciesAmount / 2]->crossingover(*allSpecies[rand() % (speciesAmount - 1) - speciesAmount / 2]);
		}
	}
}

void Population::showBest() {
	sort();
	cout << "Самый писпособленный вид:" << endl;
	allSpecies[speciesAmount - 1]->show();
}