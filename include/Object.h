#pragma once
#include "common.h"


#define STONE_N '#'
#define PREY_N 'f'
#define PREDATOR_N 'S'

class Ocean;
class Cell;

class Object
{
	friend Ocean;
	friend Cell;
protected:
	static unsigned int count;
	unsigned int liveTime;
	unsigned int reproduct_limit;
	bool eaten_f = false;
	Cell * cell;
public:
	Object(Cell * = nullptr);
	virtual ~Object();
	void setLive(unsigned int liveTime);
	void setCell(Cell* cell);
	virtual void live() = 0;
	virtual char getName() = 0;
	unsigned int getLive();
	Cell * getCell();
	void decreaseLim();
	bool is_eaten();
	void eatMe();

};
