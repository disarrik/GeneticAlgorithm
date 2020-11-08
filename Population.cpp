#include "Population.h"


//определение класса с прототипами
class Population
{
	class Species;
	int speciesAmount;
	int chromosomesAmount;
	int genesAmount;
	Species *species;
	//int (*fitness)(); //не нужна дл€ класса всей попул€ции
	void sort();
public:
	Population(int speciesAmount, int сhromosomesAmount, int genesAmount, int (*fitness)());
	void NextGeneration(int steps = 0);

};


//определение методов класса и вложенных классов
Population::Population(int speciesAmount, int сhromosomesAmount, int genesAmount, int (*fitness)()) {
	this->speciesAmount = speciesAmount;
	this->chromosomesAmount = chromosomesAmount;
	this->genesAmount = genesAmount;
}


