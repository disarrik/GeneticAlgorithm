#pragma once
#include <vector>

using namespace std;

//---------------------------------����������� ������ Population � �����������----------------------------
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
	Population(int speciesAmount, int refreshingAmount, int �hromosomesAmount, int genesAmount, int mutationChance, int (*fitness)(vector<vector<int>>));
	void NextGeneration(int steps);
	void show();
	void showBest();
};


//-------------------------����������� ������ Species, ���������� � Population--------------------------------
class Population::Specie {
	int chromosomesAmount;
	int genesAmount;
	int mutationChance;
	vector<vector<int>> chromosomes; //��������� ������������� ������[���������][���]
	int (*fitness)(vector<vector<int>>);
public:
	Specie(int chromosomesAmount, int genesAmount, int mutationChance, int (*fitness)(vector<vector<int>>));
	int fitnessMethod();
	void show();
	Specie crossingover(Specie second);
};