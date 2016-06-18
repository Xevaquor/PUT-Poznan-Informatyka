__author__ = 'Mateusz Bednarski'

from utils import *

def QuickSortIterative(A):
	iqsort(A,0, len(A) - 1)


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

def iqsort(a, l, h):
	stack = []
	stack.append(l)
	stack.append(h)


	while len(stack) > 0:
		h = stack.pop()
		l = stack.pop()
		p = part(a, l,h)

		if p - 1 > l:
			stack.append(l)
			stack.append(p-1)

		if p + 1 < h:
			stack.append(p+1)
			stack.append(h)

if __name__ == '__main__':

	dd = generate_random_sequence(100000, 0, 1000)
	print measure_exe_time(QuickSort, dd)
	print is_sorted_desc(dd)
	print dd