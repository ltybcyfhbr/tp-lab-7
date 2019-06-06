#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <ctime>
#include <time.h>
#include <iterator>
#include <algorithm>
#include  <string>

typedef size_t coord_t;

struct Pair
{
	int x; // 0..M-1
	int y; // 0..N-1
};

const size_t N = 35;
const  size_t M = 65;