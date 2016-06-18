__author__ = 'Mateusz Bednarski'

from utils import swap


def bubble(collection):
	n = len(collection)
	for i in range(0, n - 1):
		no_change = True
		for j in range(0, n - i - 1):
			if collection[j + 1] < collection[j]:
				swap(collection, j, j + 1)
				no_change = False
		if no_change:
			return






