#pragma once

#include "common.h"
#include "Object.h"
#include "Ocean.h"

class Ocean;
class Cell
{
	friend Ocean;
private:
	Pair crd;
	Object *obj = nullptr;
	Ocean *ocean;
public:
	Cell(Pair p = { 0, 0 }, Ocean* oc = nullptr)
	{
		crd = p;
		ocean = oc;
	}
	void init(Pair p, Ocean* oc);
	void setObject(Object * obj);
	void killMe();
	void killObj();
	void byeObj();
	unsigned int getCount();
	Object* getObject() const;
	Pair  getCord();
	Ocean * getOcean();
};
