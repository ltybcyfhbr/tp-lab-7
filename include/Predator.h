#pragma once

#include "Object.h"
#include "Cell.h"
#include "Ocean.h"

class Predator : public Object
{
	friend Cell;
private:
	static char name;
	static unsigned int count;
	unsigned int reproduct_limit = 2;
public:
	Predator(Cell * c);
	~Predator();
	void live();
	void move();
	bool eat();
	void reproduce();
	static unsigned int getCount();
	char getName();

};
