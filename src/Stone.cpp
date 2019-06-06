#include "Stone.h"


char  Stone::name = STONE_N;
unsigned int Stone::count = 0;

Stone::Stone(Cell * c) :Object(c)
{
	this->liveTime = 10000;
};
Stone::~Stone() {

};

void Stone::live()
{
	liveTime--;
	if (liveTime == 0)
	{
		cell->killMe();
	}

};
unsigned int Stone::getCount()
{
	return count;
};
char Stone::getName()
{
	return name;
};