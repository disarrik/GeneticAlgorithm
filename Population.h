#pragma once
#include <vector>

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
	int (*fitness)(vector<vector<int>>);
	vector<Specie*> allSpecies;
	void sort();
public:
	Population(int speciesAmount, int refreshingAmount, int сhromosomesAmount, int genesAmount, int mutationChance, int (*fitness)(vector<vector<int>>));
	void NextGeneration(int steps);
	void show();
	void showBest();
};


//-------------------------определение класса Species, вложенного в Population--------------------------------
class Population::Specie {
	int chromosomesAmount;
	int genesAmount;
	int mutationChance;
	vector<vector<int>> chromosomes; //двумерный односвязанный список[хромосома][ген]
	int (*fitness)(vector<vector<int>>);
public:
	Specie(int chromosomesAmount, int genesAmount, int mutationChance, int (*fitness)(vector<vector<int>>));
	int fitnessMethod();
	void show();
	Specie crossingover(Specie second);
};