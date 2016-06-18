from matplotlib.mlab import binary_repr
from utils import measure_exe_time
import numpy as np
import matplotlib.pyplot as plt

__author__ = 'Mateusz Bednarski'
from numpy import binary_repr


def prepend(item, collection):
	collection = collection.insert(0, item)


def generate_gray_codes_recursive(order):
	if order == 1:
		return ["0", "1"]

	top = generate_gray_codes_recursive(order - 1)
	prepend(0, top)
	low = generate_gray_codes_recursive(order - 1)
	low.reverse()
	prepend(1, low)

	return top + low


def wdi(order):
	if order == 1:
		return ["0", "1"]

	top = list(wdi(order - 1))
	down = list(top)
	down.reverse()
	for i in range(0, len(top)):
		top[i] = "0" + top[i]
	for j in range(0, len(down)):
		down[j] = "1" + down[j]

	return top + down


def generate_gray_codes(count):
	codes = []
	for x in range(count):
		codes.append(x ^ (x >> 1))
	return codes


def bench():
	probes = range(1, 21)
	repeats = 1

	rec = np.zeros((len(probes), 3))
	ite = np.zeros((len(probes), 3))

	ri = []
	row = 0
	for probe in probes:
		print probe
		rr = []
		for i in range(repeats):
			rtime = measure_exe_time(generate_gray_codes, 2 ** probe)
			ri.append(rtime)
			#ri.append(measure_exe_time(generate_gray_codes, probe))
			rr.append(measure_exe_time(wdi, probe))

		rmean = np.mean(rr)
		rmax = np.max(rr)
		rmin = np.min(rr)
		rec[row, :] = [rmean, rmax, rmin]

		imean = np.mean(ri)
		imax = np.max(ri)
		imin = np.min(ri)

		ite[row, :] = [imean, imax, imin]
		row += 1

	p1, = plt.plot(probes, ite[:, 0])
	p2, = plt.plot(probes, rec[:, 0])
	plt.legend([p1, p2], ['Iterative', 'Recursive'], loc=2)
	plt.xlabel('Number of bits in code')
	plt.ylabel('Execution time [s]')
	plt.savefig('gray.png')
	plt.show()


if __name__ == '__main__':
	#digits = input('Podaj dlugosc kodu: ')
	#digits = 2
	#codes = generate_gray_codes(2 ** digits)

	#for c in codes:
	#	print binary_repr(c, width=digits)

	#print '*****recursive*****'

	#it = wdi(digits)
	#for c in it:
	#	print c

	bench()