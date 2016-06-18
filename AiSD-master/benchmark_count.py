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

import numpy as np

b_params = [10, 1000, 5000, 10000, 20000, 35000, 50000, 70000, 85000, 100000,200000,500000,1000000]

#probe_sizes = [10,100, 1000, 10000,20000]

repeats = 5


def single_algo(gen):
	dd = np.zeros((1 + repeats, len(b_params)))
	dd[0, :] = b_params

	#to fill
	algo = shell_sort

	probeIndex = 0
	too_deep = False
	for probe in b_params:
		if too_deep:
			break
		print 'Probe size ', probe, '(Index ', probeIndex, ')...'
		for row in range(1, repeats + 1):
			print 'Repeat ', row, '...'
			data = gen(100000, max_val=probe)
			try:
				perf = measure_exe_time(algo, data)
				dd[row, probeIndex] = perf
				print perf
			except RuntimeError:
				dd[row, probeIndex] = 0
				too_deep = True

		probeIndex += 1

	return dd

if __name__ == '__main__':
	setrecursionlimit(10000)
	print 'random'
	random = single_algo(generate_random_sequence)
	print 'asc'
	asc = single_algo(generate_ascending_sequence)
	print 'desc'
	desc = single_algo(generate_descending_sequence)
	print 'v'
	v = single_algo(generate_v_sequence)

	#print  measure_exe_time(QuickSortIterative, generate_ascending_sequence(20000))

	#to fill
	hdr = 'csort2'
	np.savetxt('csort_rnd2', random, header=hdr)
	np.savetxt('csort_asc2', asc,    header=hdr)
	np.savetxt('csort_desc2', desc,  header=hdr)
	np.savetxt('csort_v2', v, 		 header=hdr)
