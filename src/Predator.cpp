#include "Predator.h"

char Predator::name = PREDATOR_N;
unsigned int Predator::count = 0;


Predator::Predator(Cell * c) :Object(c)
{
	this->liveTime = 17;
};
Predator::~Predator() {};
void Predator::live()
{
	move();
	if (reproduct_limit != 0)
		reproduce();
	if (!eat() && liveTime>3)
		liveTime -= 3;
	else
		liveTime--;
	if (liveTime == 0)
	{
		cell->killMe();
	}

};
unsigned int Predator::getCount()
{
	return count;
};
char Predator::getName()
{
	return name;
};
void Predator::move()
{
	Pair cord = cell->getCord();

	Cell * neigh = cell->getOcean()->getFreeCell(cord);
	if (neigh != nullptr)
	{
		this->getCell()->byeObj();
		neigh->setObject(this);
		this->cell = neigh;
	}

}
bool Predator::eat()
{
	Pair cord = cell->getCord();
	Cell * neigh = cell->getOcean()->getOccupiedCell(cord, PREY_N);
	if (neigh && !neigh->getObject()->is_eaten())
	{
		neigh->getObject()->eatMe();
		neigh->getObject()->setLive(1);
		liveTime += 2;
		return true;
	}
	return false;
}
void Predator::reproduce()
{
	Pair cord = cell->getCord();
	Cell * partner = cell->getOcean()->getOccupiedCell(cord, PREDATOR_N);
	if (partner && rand() % 4 == 1)
	{
		Cell * neigh = cell->getOcean()->getFreeCell(cord);
		if (neigh)
		{
			Object * child = new Predator(neigh);
			neigh->setObject(child);
			cell->getOcean()->setStuff(child);
			neigh->getObject()->decreaseLim();
			this->decreaseLim();
		}
	}

}