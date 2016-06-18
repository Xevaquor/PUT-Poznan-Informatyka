__author__ = 'Mateusz Bednarski'

from utils import *

def QuickSort(A):
	qsort(A,0, len(A) -1)


def qsort(a, lo, hi):
	if hi <= lo:
		return
	j = part(a, lo, hi);
	qsort(a, lo, j-1)
	qsort(a, j+1, hi)

def part(a, lo, hi):
	i = lo
	j = hi+1
	v = a[lo]
	while True:
		i += 1
		while a[i] > v:
			if i == hi:
				break
			i += 1
		j -= 1
		while v > a[j]:
			if j == lo:
				break
			j -= 1
		if i >= j:
			break
		a[i], a[j] = a[j], a[i]
	a[lo], a[j] = a[j], a[lo]
	return j
if __name__ == '__main__':

	dd = generate_random_sequence(100000,0,1000)
	print  measure_exe_time(QuickSort, dd)
	print is_sorted_desc(dd)
	print dd