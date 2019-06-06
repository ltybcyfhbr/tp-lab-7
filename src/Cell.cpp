#include "Cell.h"

void Cell::init(Pair p, Ocean* oc)
{
	crd = p;
	ocean = oc;
}

Object* Cell::getObject() const
{
	if (obj)
		return obj;
	else
		return nullptr;
}
		
void Cell::setObject(Object *obj) 
{
		this->obj = obj;
}

void Cell::killMe()
{
	if (obj)
	{
		delete obj;
		this->obj = nullptr;
	}
}
void Cell::killObj()
{
	obj = nullptr;
}
void Cell::byeObj()
{
	obj->setCell(nullptr);
	obj = nullptr;

}
Pair Cell::getCord()
{
	return crd;
}
Ocean * Cell::getOcean()
{
	return ocean;
}
unsigned int Cell::getCount()
{
	if (obj)
		return obj->count;
	else
		return 0;
}