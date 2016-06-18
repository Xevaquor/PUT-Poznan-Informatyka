// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <Windows.h>
#include <cmath>

const long long num_steps = 1000000000;


void sequential()
{
	double step;
	clock_t start, stop;
	double x, pi, sum = 0.0;
	int i;
	step = 1. / (double)num_steps;
	start = clock();
	for (i = 0; i < num_steps; i++)
	{
		x = (i + .5)*step;
		sum = sum + 4.0 / (1. + x*x);
	}

	pi = sum*step;
	stop = clock();

	printf("%s\n", abs(pi - 3.1415) < 0.001 ? "OK" : "INCORRECT RESULT");
	printf("time: %f\n", ((double)(stop - start) / 1000.0));
}

void ompfor(void)
{
	double step;
	clock_t start, stop;
	double pi, sum = 0.0;
	int i;
	step = 1. / (double)num_steps;
	start = clock();
#pragma omp parallel for num_threads(4) schedule(static)
	for (i = 0; i < num_steps; i++)
	{
		double x = (i + .5)*step;
		sum = sum + 4.0 / (1. + x*x);
	}
	pi = sum*step;
	stop = clock();
	printf("%s\n", abs(pi - 3.1415) < 0.001 ? "OK" : "INCORRECT RESULT");
	printf("time: %f\n", ((double)(stop - start) / 1000.0));
}

void atomic(void)
{
	double step;
	clock_t start, stop;
	double pi, sum = 0.0;
	int i;
	step = 1. / (double)num_steps;
	start = clock();
#pragma omp parallel for num_threads(4) schedule(static)
	for (i = 0; i < num_steps; i++)
	{
		double 	x = (i + .5)*step;
#pragma omp atomic
		sum += 4.0 / (1. + x*x);
	}

	pi = sum*step;
	stop = clock();

	printf("%s\n", abs(pi - 3.1415) < 0.001 ? "OK" : "INCORRECT RESULT");
	//printf("val:  %15.12f\n", pi);
	printf("time: %f\n", ((double)(stop - start) / 1000.0));
}

void reduction(void)
{
	double step;
	clock_t start, stop;
	double pi, sum = 0.0;
	int i;
	step = 1. / (double)num_steps;
	start = clock();
#pragma omp parallel for reduction(+:sum) num_threads(4) schedule(static)
	for (i = 0; i < num_steps; i++)
	{
		double x = (i + .5)*step;
		sum = sum + 4.0 / (1. + x*x);
	}
	pi = sum*step;
	stop = clock();
	printf("%s\n", abs(pi - 3.1415) < 0.001 ? "OK" : "INCORRECT RESULT");
	printf("time: %f\n", ((double)(stop - start) / 1000.0));
}

void false_sharing_parallel(void)
{
	double step;
	volatile double tab[4] = { 0 };
	clock_t start, stop;
	double pi, sum = 0.0;
	int i;
	step = 1. / (double)num_steps;
	start = clock();
#pragma omp parallel num_threads(4)
	{
		int id = omp_get_thread_num();
#pragma omp for reduction(+:sum) schedule(static)
		for (i = 0; i < num_steps; i++)
		{
			double x = (i + .5)*step;
			tab[id] += 4.0 / (1. + x*x);
		}
#pragma omp atomic
		sum += tab[id];
	}

	pi = sum*step;
	stop = clock();

	printf("%s\n", abs(pi - 3.1415) < 0.001 ? "OK" : "INCORRECT RESULT");
	printf("time: %f\n", ((double)(stop - start) / 1000.0));
}


void false_sharing_sequential(void)
{
	double step;
	volatile double tab[4] = { 0 };
	clock_t start, stop;
	double pi, sum = 0.0;
	int i;
	step = 1. / (double)num_steps;
	start = clock();
#pragma omp parallel num_threads(1)
	{
		int id = omp_get_thread_num();
#pragma omp for reduction(+:sum) schedule(static)
		for (i = 0; i < num_steps; i++)
		{
			double x = (i + .5)*step;
			tab[id] += 4.0 / (1. + x*x);
		}
#pragma omp atomic
		sum += tab[id];
	}

	pi = sum*step;
	stop = clock();

	printf("%s\n", abs(pi - 3.1415) < 0.001 ? "OK" : "INCORRECT RESULT");
	printf("time: %f\n", ((double)(stop - start) / 1000.0));
}

void memory_line(void)
{
	float step;
	typedef float float_t;
	volatile float_t tablica[10000] = { 0 };
	for (int q = 0; q < 10000; q++)
	{
		ZeroMemory((char *)tablica, 10000 * sizeof(float_t));
		clock_t start, stop;
		float_t x, pi, sum = 0.0;
		int i;
		step = 1. / (float_t)num_steps;
		start = clock();
#pragma omp parallel num_threads(2)
		{
			int id = omp_get_thread_num();
#pragma omp for schedule(static)
			for (i = 0; i < num_steps; i++)
			{
				float_t x = (i + .5)*step;
				tablica[q + id] += 4.0 / (1. + x*x);
			}
#pragma omp atomic
			sum += tablica[q + id];
		}

		pi = sum*step;
		stop = clock();

		printf("%s\n", abs(pi - M_PI) < 0.001 ? "OK" : "INCORRECT RESULT");
		printf("%d time: %f\n", q, ((double)(stop - start) / 1000.0));
	}
	exit(0);
}


void affinity_1_to_1(void)
{
	double step;
	clock_t start, stop;
	double x, pi, sum = 0.0;
	int i;
	step = 1. / (double)num_steps;
	start = clock();
#pragma omp parallel num_threads(4)
	{
		int id = omp_get_thread_num();
		DWORD_PTR mask = (1 << id);
		// DWORD_PTR mask = (1 << id / 2); dla powinowactwa parami
		SetThreadAffinityMask(GetCurrentThread(), mask);
		
#pragma omp for reduction(+:sum) schedule(static)
		for (i = 0; i < num_steps; i++)
		{
			x = (i + .5)*step;
			sum = sum + 4.0 / (1. + x*x);
		}
	}
	pi = sum*step;
	stop = clock();

	printf("%s\n", abs(pi - M_PI) < 0.001 ? "OK" : "INCORRECT RESULT");

	printf("time: %f\n", ((double)(stop - start) / 1000.0));
}

void affinity_pairs(void)
{
	double step;
	clock_t start, stop;
	double x, pi, sum = 0.0;
	int i;
	step = 1. / (double)num_steps;
	start = clock();
#pragma omp parallel num_threads(4)
	{
		int id = omp_get_thread_num();
		DWORD_PTR mask = (1 << id / 2);
		auto res = SetThreadAffinityMask(GetCurrentThread(), mask);
		//printf("id %d res: %d\n", id, mask);
#pragma omp for reduction(+:sum) schedule(static)
		for (i = 0; i < num_steps; i++)
		{
			x = (i + .5)*step;
			sum = sum + 4.0 / (1. + x*x);
		}
	}
	pi = sum*step;
	stop = clock();

	printf("%s\n", abs(pi - M_PI) < 0.001 ? "OK" : "INCORRECT RESULT");

	printf("time: %f\n", ((double)(stop - start) / 1000.0));
}
void affinity_auto(void)
{
	double step;
	clock_t start, stop;
	double x, pi, sum = 0.0;
	int i;
	step = 1. / (double)num_steps;
	start = clock();
#pragma omp parallel for reduction(+:sum) schedule(static) num_threads(4)
		for (i = 0; i < num_steps; i++)
		{
			x = (i + .5)*step;
			sum = sum + 4.0 / (1. + x*x);
		}
	pi = sum*step;
	stop = clock();

	printf("%s\n", abs(pi - M_PI) < 0.001 ? "OK" : "INCORRECT RESULT");
	printf("time: %f\n", ((double)(stop - start) / 1000.0));
}


int main(int argc, char* argv[])
{
	//memory_line();
	bool check_affinity = true;

	const int PASSES = 3;
	if (check_affinity)
	{
		printf("===affinity 1 to 1===\n");
		for (size_t i = 0; i < PASSES; i++)
		{
			affinity_1_to_1();
		}

		printf("===affinity pairs===\n");
		for (size_t i = 0; i < PASSES; i++)
		{
			affinity_pairs();
		}

		printf("===affinity auto===\n");
		for (size_t i = 0; i < PASSES; i++)
		{
			affinity_auto();
		}
		exit(0);
	}

	printf("===sequential===\n");
	for (size_t i = 0; i < PASSES; i++)
	{
		sequential();
	}

	printf("===omp for===\n");
	for (size_t i = 0; i < PASSES; i++)
	{
		ompfor();
	}

	printf("===atomic===\n");
	for (size_t i = 0; i < PASSES; i++)
	{
		atomic();
	}

	printf("===reduction===\n");
	for (size_t i = 0; i < PASSES; i++)
	{
		reduction();
	}

	printf("===false sharing parallel===\n");
	for (size_t i = 0; i < PASSES; i++)
	{
		false_sharing_parallel();
	}

	printf("===false sharing sequential===\n");
	for (size_t i = 0; i < PASSES; i++)
	{
		false_sharing_parallel();
	}

	return 0;

	double step;

	omp_set_num_threads(2);
	volatile double tablica[10000] = { 0 };
	for (int q = 0; q < 10000; q++)
	{
		ZeroMemory((char *)tablica, 10000 * sizeof(double));
		clock_t start, stop;
		double x, pi, sum = 0.0;
		int i;
		step = 1. / (double)num_steps;
		start = clock();
		//#pragma omp parallel for reduction(+:sum)
#pragma omp parallel
		{
			double suml = 0;
			int id = omp_get_thread_num();
#pragma omp for schedule(static)
			for (i = 0; i < num_steps; i++)
			{
				double x = (i + .5)*step;
				tablica[q + id] += 4.0 / (1. + x*x);
			}
#pragma omp atomic
			sum += tablica[q + id];
		}

		pi = sum*step;
		stop = clock();

		printf("Wartosc liczby PI wynosi %15.12f\n", pi);
		//printf("%d: Czas przetwarzania wynosi %f sekund\n", q,((double)(stop - start) / 1000.0));
		printf("%f\n", (double)(stop - start));
	}
	return 0;
}


