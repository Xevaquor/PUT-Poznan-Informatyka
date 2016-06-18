

#include <iostream>
#include<cctype>
#include <stdlib.h>
#include <conio.h>
#include <cstdarg>
#include <ctime>

#include "AvlTree.h"
#include "BstTree.h"
#include "RedBlackTree.h"

using namespace std;

extern void Perf();

int main(int argc, char** argv)
{
	//Perf();

	RedBlackTree<int> xd;

	xd.Insert(1);
	xd.Insert(2);
	xd.Insert(3);
	xd.Insert(4);
	xd.Insert(5);
	xd.Insert(6);
	xd.Insert(7);
	xd.Insert(8);
	xd.Insert(9);
	xd.Insert(10);
	xd.Insert(16);
	xd.Insert(17);

	xd.Print();

	auto c = xd.Find(9);

	system("pause");

	return 0;
}

