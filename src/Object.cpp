#include "Object.h"


unsigned int Object::count = 0;

Object::Object(Cell * cell)
{
	this->cell = cell;
	count++;
};
Object::~Object()
{

	count--;
};

void Object::setCell(Cell* cell)
{
	this->cell = cell;
};
Cell * Object::getCell()
{
	return cell;
}

unsigned int Object::getLive()
{
	return liveTime;
}

void Object::setLive(unsigned int liveTime)
{
	this->liveTime = liveTime;
}

void Object::decreaseLim()
{
	reproduct_limit--;
}
bool Object::is_eaten()
{
	return eaten_f;
}
void Object::eatMe()
{
	eaten_f = true;
}