from matplotlib import legend

__author__ = 'Mateusz Bednarski'

import matplotlib.pyplot as plt
import numpy as np

def analyse(f):
	raw = np.loadtxt(f)
	x = raw[0, :]
	dd = raw[1:, :]
	str = np.array_str(dd)
	mean = np.mean(dd, axis=0)
	minima = mean - np.amin(dd, axis=0)
	maxima = np.amax(dd, axis=0) - mean

	errors = [minima, maxima]

	return x, mean, errors

if __name__ == '__main__':
	#f = raw_input('File to analyse: ')
	x, mean, errors = analyse   ('kadane_rnd2')
	x1, mean1, errors1 = analyse('kadane_asc2')
	x2, mean2, errors2 = analyse('kadane_desc2')


	p, h ,d= plt.errorbar(x, mean, errors,    fmt='r-')
	p1, h,d = plt.errorbar(x1, mean1, errors1, fmt='g-')
	p2, h,d = plt.errorbar(x2, mean2, errors2, fmt='b-')

	plt.legend([p,p1,p2], ['random', 'ascending', 'descending'], loc=2)
	#plt.axis('equal')
	plt.ylabel('Execution time [s]')
	plt.xlabel('Maximum value. n = const = 100000')
	plt.title('Stock problem')

	plt.savefig('stock_const_n' + '.png')
	plt.show()


"""
	trimIndex = 0
	for i in range(0, len(x2)):
		if mean2[i] == 0:
			trimIndex = i
			break

	mean2 = mean2[:trimIndex]
	x2 = x2[:trimIndex]
	mean1 = mean1[:trimIndex]
	x1 = x1[:trimIndex]

	e2u = errors2[0]
	e2l = errors2[1]
	e2u = e2u[:trimIndex]
	e2l = e2l[:trimIndex]
	errors2 = [e2l, e2u]
	errors1 = errors2"""