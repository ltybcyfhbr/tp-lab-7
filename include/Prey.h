#pragma once

#include "Object.h"
#include "Cell.h"
#include "Ocean.h"


class Cell;
class Ocean;
class Prey : public Object
{
	friend Cell;
	friend Ocean;
private:
	static char name;
	static unsigned int count;
	unsigned int reproduct_limit = 10;
public:
	Prey(Cell * c);
	~Prey();
	void live();
	void move();
	void reproduce();
	static unsigned int getCount();
	char getName();
};
