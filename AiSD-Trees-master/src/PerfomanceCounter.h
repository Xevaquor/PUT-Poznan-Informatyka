#pragma once
#include <functional>
#include <vector>

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#else
#error Unsupported platform (not Win32)
#endif
#include "BstTree.h"
#include "AvlTree.h"
#include "RedBlackTree.h"

class PerfomanceCounter
{
	__int64 frequency;

public:
	double MeasureExecutionTime(std::function<void(void)> func) const;
	double MeasureExecutionTime(std::function<void(std::vector<int>)> func, std::vector<int> &param) const;
	double MeasureExecutionTime(std::function<void(BstTree<int>*)> func, BstTree<int> *) const;
	double MeasureExecutionTime(std::function<void(AvlTree<int>*)> func, AvlTree<int> *param) const;
	double MeasureExecutionTime(std::function<void(RedBlackTree<int>*, int)> func, RedBlackTree<int> *param, int n) const;
	PerfomanceCounter();
};
