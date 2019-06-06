#pragma once
#include "Object.h"
#include "Cell.h"
#include "Ocean.h"



class Stone : public Object
{
	friend Cell;
private:
	static unsigned int count;
	static char name;
public:
	Stone(Cell * c);
	~Stone();
	void live();
	static unsigned int getCount();
	char getName();

};