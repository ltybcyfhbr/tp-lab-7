#include "Prey.h"
#include <iostream>

char Prey::name = PREY_N;
unsigned int Prey::count = 0;

Prey::Prey(Cell * c) :Object(c)
{
	this->liveTime = 20;
}
Prey::~Prey() {};
void Prey::live()
{
	move();
	if (reproduct_limit != 0)
		reproduce();
	if (!eaten_f)
		liveTime--;
	if (liveTime == 0)
		cell->killMe();
}
unsigned int Prey::getCount()
{
	return count;
}
char Prey::getName()
{
	return name;
}
void Prey::move()
{
	Pair cord = cell->getCord();

	Cell * neigh = cell->getOcean()->getFreeCell(cord);
	if (neigh)
	{
		this->getCell()->byeObj();
		neigh->setObject(this);
		this->cell = neigh;
	}

}
void Prey::reproduce()
{
	Pair cord = cell->getCord();
	Cell * partner = cell->getOcean()->getOccupiedCell(cord, PREY_N);
	if (partner && rand() % 4 == 1)
	{
		Cell * neigh = cell->getOcean()->getFreeCell(cord);
		if (neigh)
		{
			Object * child = new Prey(neigh);
			neigh->setObject(child);
			cell->getOcean()->setStuff(child);
			neigh->getObject()->decreaseLim();
			this->decreaseLim();
		}
	}

}