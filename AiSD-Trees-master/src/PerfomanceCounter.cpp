#include "PerfomanceCounter.h"

PerfomanceCounter::PerfomanceCounter()
{
	LARGE_INTEGER clockFrequency;
	QueryPerformanceFrequency(&clockFrequency);
	frequency = clockFrequency.QuadPart;
}

double PerfomanceCounter::MeasureExecutionTime
(std::function<void(void)> func) const
{
	LARGE_INTEGER start, stop;
	QueryPerformanceCounter(&start);

	func();

	QueryPerformanceCounter(&stop);
	return (stop.QuadPart - start.QuadPart) * 1.0 / frequency;
}

double PerfomanceCounter::MeasureExecutionTime(std::function<void(std::vector<int>)> func, std::vector<int> &param) const
{
	LARGE_INTEGER start, stop;
	QueryPerformanceCounter(&start);

	func(param);

	QueryPerformanceCounter(&stop);
	return (stop.QuadPart - start.QuadPart) * 1.0 / frequency;

}
double PerfomanceCounter::MeasureExecutionTime(std::function<void(BstTree<int>*)> func, BstTree<int> *param) const
{

	LARGE_INTEGER start, stop;
	QueryPerformanceCounter(&start);

	func(param);

	QueryPerformanceCounter(&stop);
	return (stop.QuadPart - start.QuadPart) * 1.0 / frequency;
}
double PerfomanceCounter::MeasureExecutionTime(std::function<void(AvlTree<int>*)> func, AvlTree<int> *param) const
{

	LARGE_INTEGER start, stop;
	QueryPerformanceCounter(&start);

	func(param);

	QueryPerformanceCounter(&stop);
	return (stop.QuadPart - start.QuadPart) * 1.0 / frequency;
}
double PerfomanceCounter::MeasureExecutionTime(std::function<void(RedBlackTree<int>*,int)> func, RedBlackTree<int> *param,int n) const
{

	LARGE_INTEGER start, stop;
	QueryPerformanceCounter(&start);

	func(param, n);

	QueryPerformanceCounter(&stop);
	return (stop.QuadPart - start.QuadPart) * 1.0 / frequency;
}
