#include <iostream>
#include "Ocean.h"
#include "common.h"
#include "Cell.h"
#include "Predator.h"
#include "Stone.h"
#include "Prey.h"

using namespace std;


int main()
{
	srand(time(nullptr));
	Ocean *atlantic = new Ocean;
	atlantic->addObjects(250);
	atlantic->run(10);
	system("pause");
}