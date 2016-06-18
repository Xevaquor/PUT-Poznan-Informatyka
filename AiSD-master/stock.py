__author__ = 'Mateusz Bednarski'
import math
from random import random
import matplotlib.pyplot as plt
from time import clock
import numpy as np
from generators import generate_random_sequence


def wall_street(n):
	stock = n * [100]
	for i in range(1, n - 2):
		stock[i + 1] = stock[i] + math.cos(i * 10) * random()
	return stock


def max_subarray(a):
	max_start_index = 0
	max_end_index = 0
	max_sum = -9223372036854775807

	cumulative_sum = 0
	max_start_index_until_now = 0

	current_index = 0
	while current_index < len(a):
		each_array_item = a[current_index]
		cumulative_sum += each_array_item

		if cumulative_sum > max_sum:
			max_sum = cumulative_sum
			max_start_index = max_start_index_until_now
			max_end_index = current_index
		elif cumulative_sum < 0:
			max_start_index_until_now = current_index + 1
			cumulative_sum = 0

		current_index += 1

	return max_sum, max_start_index, max_end_index


def plot_stock():
	stock = wall_street(1100)
	plt.plot(range(1, 1101), stock)
	plt.show()


def kadane(A):
	maxSum = -9223372036854775807
	maxLeft = 0
	maxRight = 0
	currentMax = 0
	left = 0
	right = 0
	for i in range(0, len(A)):
		currentMax =currentMax+  A[i]
		if currentMax > maxSum:
			maxSum = currentMax
			right = i;
			maxLeft = left
			maxRight = right
		if currentMax < 0:
			currentMax = 0
			left = i + 1
			right = i + 1

	return maxSum, maxLeft, maxRight

def prepare(data):
	out = [0] * len(data)
	for i in range(0, len(data) - 1):
		out[i + 1] = data[i + 1] - data[i]
	return out

probes = [10, 100, 200, 500, 1000, 5000, 10000, 25000, 50000 ] #, 100000, 250000, 500000, 750000, 1000000]
b_param = [10, 100, 200, 500, 1000, 5000, 10000, 25000, 50000, 100000, 250000, 500000, 750000, 1000000]

repeats = 10

def const_b():
	results = np.zeros(len(probes))
	errors = np.zeros(len(probes))
	row = 0
	for probe in probes:
		passing = []
		r = 0
		for i in range(repeats):
			print probe
			data = generate_random_sequence(probe, max_val=100000)
			start = clock()
			dd = prepare(data)
			kadane(dd)
			stop = clock()
			passing.append (stop - start)
			r+=1
		mean = np.mean(passing)
		err = np.std(passing)
		results[row] = mean
		errors[row] = err
		row += 1
	return results, errors

def const_n():
	results = np.zeros(len(probes))
	errors = np.zeros(len(probes))
	row = 0
	for b in b_param:
		passing = []
		r = 0
		for i in range(repeats):
			print b
			data = generate_random_sequence(100000, max_val=b)
			start = clock()
			dd = prepare(data)
			kadane(dd)
			stop = clock()
			passing.append (stop - start)
			r+=1
		mean = np.mean(passing)
		err = np.std(passing)
		results[row] = mean
		errors[row] = err
		row += 1
	return results, errors


def bench():
	results = []
	for probe in probes:
		print probe
		data = wall_street(probe)
		prepared = prepare(data)
		start = clock()
		kadane(prepared)
		stop = clock()
		results.append(stop - start)

	plt.plot(probes, results)
	plt.show()


def measure():
	yb, eb = const_b()
	yn, en = const_n()
	plt.errorbar(probes, yb, yerr=eb)
	plt.errorbar(probes, yb, yerr=eb)
	plt.show()

#dd = [1, 2, 3, -4, 5, 6, 7, -8, -9]
#print maximum_subarray(dd, 0, len(dd) - 1)

if __name__ == '__main__':
	measure()
	#dd = [10, 2, 50, 70]
	#xd = prepare(dd)
	#print xd
	#print kane(xd)






