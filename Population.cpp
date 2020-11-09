#include "Population.h"
#include <ctime>
#include <iostream>

using namespace std;

//------------------------определение методов класса Species, вложенного в Population--------------------------
Population::Specie::Specie(int chromosomesAmount, int genesAmount, int mutationChance, int (*fitness)(vector<vector<int>>)) {
	this->chromosomesAmount = chromosomesAmount;
	this->genesAmount = genesAmount;
	this->fitness = fitness;
	this->mutationChance = mutationChance;
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
	for (unsigned int i = 0; i < chromosomes.size(); i++)
	{
		for (unsigned int j = 0; j < chromosomes[i].size(); j++)
		{
			cout << chromosomes[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

Population::Specie Population::Specie::crossingover(Specie second) {
	Specie child(this->chromosomesAmount, this->genesAmount, this->mutationChance, fitness);
	for (int i = 0; i < chromosomesAmount; i++)
	{
		int border = rand() % genesAmount;
		for (int j = 0; j < border; j++)
		{
			child.chromosomes[i][j] = second.chromosomes[i][j];
			int reverse = (child.chromosomes[i][j] == 0 ? 1 : 0);
			child.chromosomes[i][j] = rand() % 101 >= mutationChance  ? child.chromosomes[i][j] : reverse;
		}
		for (int j = border; j < genesAmount; j++)
		{
			child.chromosomes[i][j] =  this->chromosomes[i][j];
			int reverse = (child.chromosomes[i][j] == 0 ? 1 : 0);
			child.chromosomes[i][j] = rand() % 101 >= mutationChance ? child.chromosomes[i][j] : reverse;
		}
	}
	return child;
}

int Population::Specie::fitnessMethod() {
	return this->fitness(this->chromosomes);
}


//------------------------определение методов класса Population--------------------------
Population::Population(int speciesAmount, int refreshingAmount, int сhromosomesAmount, int genesAmount, int mutationChance, int (*fitness)(vector<vector<int>>)) {
	srand(time(0));
	this->speciesAmount = speciesAmount;
	this->refreshingAmount = refreshingAmount;
	this->chromosomesAmount = сhromosomesAmount;
	this->mutationChance = mutationChance;
	this->genesAmount = genesAmount;
	this->fitness = fitness;
	allSpecies.resize(speciesAmount);
	for (int i = 0; i < speciesAmount; i++)
	{
		allSpecies[i] = new Specie(сhromosomesAmount, genesAmount, mutationChance, fitness);
	}
}

void Population::sort() {
	for (int i = 0; i < allSpecies.size(); i++)
	{
		for (int j = 0; j < allSpecies.size() - i - 1; j++)
		{
			if (allSpecies[j]->fitnessMethod() > allSpecies[j+1]->fitnessMethod()) {
				Specie* a = allSpecies[j];
				allSpecies[j] = allSpecies[j + 1];
				allSpecies[j + 1] = a;
			}
		}
	}
}

void Population::show() {
	sort();
	for (int i = 0; i < speciesAmount; i++)
	{
		allSpecies[i]->show();
		cout << endl;
	}
}

void Population::NextGeneration(int steps) {
	for (int i = 0; i < steps; i++)
	{
		sort();
		for (int i = 0; i < (speciesAmount / 2); i++)
		{
			delete allSpecies[i];
			allSpecies[i] = new Specie(chromosomesAmount, genesAmount, mutationChance, fitness);
			*allSpecies[i] = allSpecies[speciesAmount / 2 + (rand() % speciesAmount / 2)]->crossingover(*allSpecies[speciesAmount / 2 + (rand() % speciesAmount / 2)]);
		}
	}
}

void Population::showBest() {
	sort();
	cout << "Самый приспособленный вид:" << endl;
	allSpecies[speciesAmount - 1]->show();
}