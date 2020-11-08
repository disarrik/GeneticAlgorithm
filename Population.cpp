#include "Population.h"


//����������� ������ � �����������
class Population
{
	class Species;
	int speciesAmount;
	int chromosomesAmount;
	int genesAmount;
	Species *species;
	//int (*fitness)(); //�� ����� ��� ������ ���� ���������
	void sort();
public:
	Population(int speciesAmount, int �hromosomesAmount, int genesAmount, int (*fitness)());
	void NextGeneration(int steps = 0);

};


//����������� ������� ������ � ��������� �������
Population::Population(int speciesAmount, int �hromosomesAmount, int genesAmount, int (*fitness)()) {
	this->speciesAmount = speciesAmount;
	this->chromosomesAmount = chromosomesAmount;
	this->genesAmount = genesAmount;
}


