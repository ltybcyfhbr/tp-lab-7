#include "Ocean.h"
#include "Stone.h"
#include "Object.h"

Ocean::Ocean()
{
	cells = new Cell*[N];
	for (int i = 0; i < N; i++)
	{
		cells[i] = new Cell[M];
		for (int j = 0; j < M; j++)
			cells[i][j].init(Pair{ i, j }, this);
	}
};
Ocean::~Ocean()
{
	for (int i = 0; i < N; i++)
		delete[] cells[i];
	delete[] cells;
	for (auto item = stuff.begin(); item != stuff.end(); ++item)
		delete *item;
};
void Ocean::setStuff(Object *obj)
{
	stuff.push_back(obj);
}

void Ocean::print() const
{
	for (auto i = 0; i < N; i++)
	{
		for (auto j = 0; j < M; j++)
		{
			std::cout << (cells[i][j].getObject() ?
				cells[i][j].getObject()->getName() : '.');
		}
		std::cout << std::endl;
	}
};
void Ocean::addObjects(unsigned int count)
{
	if (count >(M - 1)*(N - 1))
	{
		throw "ERR: COUNT IS LARGER THAN N_CELLS";
		return;
	}
	while (count > 0)
	{
		int x = rand() % N;
		int y = rand() % M;
		if (cells[x][y].getObject())
			continue;
		else
		{
			unsigned int chance = rand() % 3;
			Object *born;
			switch (chance)
			{
			case 0:
				born = new Stone(&cells[x][y]);
				break;
			case 1:
				born = new Prey(&cells[x][y]);
				break;
			case 2:
				born = new Predator(&cells[x][y]);
				break;
			default:
				born = nullptr;
			}
			cells[x][y].setObject(born);
			stuff.push_back(born);
			count--;
		}
	}
};
void Ocean::run(int speed)
{
	int iter = 1;
	unsigned int* pCount = nullptr;
	while (1)
	{
		pCount = getCount();
		for (auto & obj : stuff)
		{
			obj->live();
		}
		clock_t now = clock();
		while (clock() < now + CLOCKS_PER_SEC - 100 * speed);
		system("cls");
		this->print();
		std::cout << "iter - " << iter++ << std::endl;
		removeObj();
		std::cout << "Stone- " << pCount[0] << " Prey- " << pCount[1] << " Predator- " << pCount[2] << std::endl;
		delete pCount;
	}
};


void Ocean::removeObj()
{
	std::vector < Object*> killEM;
	auto beg = stuff.begin();
	auto end = stuff.end();
	for (auto &obj : stuff)
		if (obj->getLive() == 1)
			killEM.push_back(obj);
	auto real_end = remove_if(beg, end, [](Object * obj)
	{ if (obj->getLive() == 1) { obj->getCell()->killObj(); }  return obj->getLive() == 1; });
	if (distance(real_end, end)>0)
	{
		stuff.erase(real_end, end);
		for (auto &obj : killEM)
			if (obj->getLive() == 1)
				obj->getCell()->killMe();
	}
}





unsigned int * Ocean::getCount()
{
	unsigned int * pCount = new unsigned int[3];
	pCount[0] = 0;//stones number
	pCount[1] = 0;//preys number
	pCount[2] = 0;// predator number 
	for (auto & obj : stuff)
	{
		switch (obj->getName())
		{
		case (STONE_N):
			pCount[0]++;
			break;
		case (PREDATOR_N):
			pCount[2]++;
			break;
		case (PREY_N):
			pCount[1]++;
			break;
		}
	}
	return pCount;
}

Cell * Ocean::getFreeCell(Pair cord_)
{
	std::vector<int> neigh = { 0,1,2,3,4,5,6,7 };
	std::random_shuffle(neigh.begin(), neigh.end());
	int where;
	Pair cord;
	while (1)
	{
		cord = cord_;
		if (neigh.size() == 0)
			break;
		where = neigh.back();
		neigh.pop_back();
		switch (where)
		{
		case 0:
			if (cord.x + 1 < N  && cord.y + 1 < M)
				if (cells[cord.x + 1][cord.y + 1].getObject() == nullptr)
					return  &cells[cord.x + 1][cord.y + 1];
			break;
		case 1:
			if (cord.y - 1 >= 0 && cord.x - 1 >= 0)
				if (cells[cord.x - 1][cord.y - 1].getObject() == nullptr)
					return  &cells[cord.x - 1][cord.y - 1];
			break;
		case 2:
			if (cord.x - 1 >= 0 && cord.y + 1 < M)
				if (cells[cord.x - 1][cord.y + 1].getObject() == nullptr)
					return  &cells[cord.x - 1][cord.y + 1];
			break;
		case 3:
			if (cord.x + 1 < N && cord.y - 1 >= 0)
				if (cells[cord.x + 1][cord.y - 1].getObject() == nullptr)
					return  &cells[cord.x + 1][cord.y - 1];
			break;
		case 4:
			if (cord.y + 1 > M && cord.x < N)
				if (cells[cord.x][cord.y + 1].getObject() == nullptr)
					return  &cells[cord.x][cord.y + 1];
			break;
		case 5:
			if (cord.y - 1 >= 0)
				if (cells[cord.x][cord.y - 1].getObject() == nullptr)
					return  &cells[cord.x][cord.y - 1];
			break;
		case 6:
			if (cord.x + 1 < N)
				if (cells[cord.x + 1][cord.y].getObject() == nullptr)
					return  &cells[cord.x + 1][cord.y];
			break;
		case 7:
			if (cord.x - 1 >= 0)
				if (cells[cord.x - 1][cord.y].getObject() == nullptr)
					return  &cells[cord.x - 1][cord.y];
			break;
		default:
			return nullptr;
		}
	}
	return nullptr;
}

Cell * Ocean::getOccupiedCell(Pair cord, char name)
{
	std::vector<int> neigh = { 0,1,2,3,4,5,6,7 };
	std::random_shuffle(neigh.begin(), neigh.end());
	int where;
	while (1)
	{
		if (neigh.size() == 0)
			break;
		where = neigh.back();
		neigh.pop_back();
		switch (where)
		{
		case 0:
			if (cord.x + 1 < N  && cord.y + 1 < M)
				if (cells[cord.x + 1][cord.y + 1].getObject())
					if (cells[cord.x + 1][cord.y + 1].getObject()->getName() == name)
						return  &cells[cord.x + 1][cord.y + 1];
			break;
		case 1:
			if (cord.x - 1 >= 0 && cord.y - 1 >= 0)
				if (cells[cord.x - 1][cord.y - 1].getObject())
					if (cells[cord.x - 1][cord.y - 1].getObject()->getName() == name)
						return  &cells[cord.x - 1][cord.y - 1];
			break;
		case 2:
			if (cord.x - 1 >= 0 && cord.y + 1 < M)
				if (cells[cord.x - 1][cord.y + 1].getObject())
					if (cells[cord.x - 1][cord.y + 1].getObject()->getName() == name)
						return  &cells[cord.x - 1][cord.y + 1];
			break;
		case 3:
			if (cord.x + 1 < N && cord.y - 1 >= 0)
				if (cells[cord.x + 1][cord.y - 1].getObject())
					if (cells[cord.x + 1][cord.y - 1].getObject()->getName() == name)
						return  &cells[cord.x + 1][cord.y - 1];
			break;
		case 4:
			if (cord.y + 1 < M)
				if (cells[cord.x][cord.y + 1].getObject())
					if (cells[cord.x][cord.y + 1].getObject()->getName() == name)
						return  &cells[cord.x][cord.y + 1];
			break;
		case 5:
			if (cord.y - 1 >= 0)
				if (cells[cord.x][cord.y - 1].getObject())
					if (cells[cord.x][cord.y - 1].getObject()->getName() == name)
						return  &cells[cord.x][cord.y - 1];
			break;
		case 6:
			if (cord.x + 1 < N)
				if (cells[cord.x + 1][cord.y].getObject())
					if (cells[cord.x + 1][cord.y].getObject()->getName() == name)
						return  &cells[cord.x + 1][cord.y];
			break;
		case 7:
			if (cord.x - 1 >= 0)
				if (cells[cord.x - 1][cord.y].getObject())
					if (cells[cord.x - 1][cord.y].getObject()->getName() == name)
						return  &cells[cord.x - 1][cord.y];
			break;
		default:
			return nullptr;
		}
	}
	return nullptr;
}