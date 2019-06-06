#pragma once

#include "common.h"

#include "Cell.h"
#include "Predator.h"
#include "Stone.h"
#include "Prey.h"



class Ocean
{

private:
	Cell * *cells;
	std::list<Object*> stuff;

public:
	Ocean();
	~Ocean();
	void setStuff(Object *obj);
	void addObjects(unsigned int count);
	void removeObj();
	unsigned int * getCount();
	Cell * getFreeCell(Pair cord);
	Cell *  getOccupiedCell(Pair cord, char name);
	void run(int speed);
	void print() const;
};
