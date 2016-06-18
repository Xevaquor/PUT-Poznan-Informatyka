__author__ = 'Mateusz Bednarski'

from counting_sort import counting_sort
from qsort import QuickSort
#from qsort2 import qsort1 as QuickSort
from qsort_iter import QuickSortIterative
from heap_sort import heap_sort
from shell import shell_sort
from utils import measure_exe_time
from generators import *
from sys import setrecursionlimit
from stock import kadane, prepare
from time import clock

import numpy as np

probe_sizes = [10, 1000, 10000,50000,100000,500000,750000,1000000,5000000,10000000]
b_param = [10000,100000,1000000,2500000,5000000,7500000,10000000,15000000,20000000]
#probe_sizes = [10,100, 1000, 10000,20000]

repeats = 5


def single_algo(gen):
	dd = np.zeros((len(b_param), len(probe_sizes)))
	#dd[0, :] = probe_sizes
	#dd[:, 0] = b_param

	#to fill
	algo = counting_sort

	nc = 0
	bc = 0

	for n in probe_sizes:
		bc = 0
		for b in b_param:
			print 'n=', n, ' b=', b
			r = []
			for xd in range(repeats):
				data = generate_random_sequence(n, max_val=b)

				start = clock()
				ddd = prepare(data)
				kadane(ddd)
				stop = clock()
				r.append(stop - start)
			dd[bc, nc] = np.mean(r)
			bc += 1
		nc += 1

	'''probeIndex = 0
	too_deep = False
	for probe in probe_sizes:
		if too_deep:
			break
		print 'Probe size ', probe, '(Index ', probeIndex, ')...'
		for row in range(1, repeats + 1):
			print 'Repeat ', row, '...'
			data = gen(probe)
			try:
				perf = measure_exe_time(algo, data)
				dd[row, probeIndex] = perf
				print perf
			except RuntimeError:
				dd[row, probeIndex] = 0
				too_deep = True

		probeIndex += 1'''

	return dd

if __name__ == '__main__':
	setrecursionlimit(10000)
	print 'random'
	random = single_algo(generate_random_sequence)
	'''print 'asc'
	asc = single_algo(generate_ascending_sequence)
	print 'desc'
	desc = single_algo(generate_descending_sequence)
	print 'v'
	v = single_algo(generate_v_sequence)
'''
	#print  measure_exe_time(QuickSortIterative, generate_ascending_sequence(20000))

	#to fill
	hdr = 'csort'
	np.savetxt('bnstock', random, fmt='%f', header=hdr)
