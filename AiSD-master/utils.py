__author__ = 'Mateusz Bednarski'

from random import randint
from time import clock


def swap(collection, a, b):
	assert (a < len(collection) and b < len(collection))
	tmp = collection[a]
	collection[a] = collection[b]
	collection[b] = tmp


def generate_random_sequence(size, min_val=0, max_val=100):
	""" Generates random sequence of numbers
	:type max_val: int
	:type min_val: int
	:param size: Sequence size
	:param min_val: Min value(inclusive)
	:param max_val: Max value(exclusive)
	:return: Generated sequence
	"""
	seq = []
	for i in range(size):
		seq.append(randint(min_val, max_val))
	return seq


def is_sorted(collection):
	"""Checks if given collection is sorted (ascending)

	:param collection: Collection to check
	:return: True if is sorted
	"""
	if len(collection) <= 1:
		return True

	prev = collection[0]
	for i in range(1, len(collection)):
		if prev > collection[i]:
			return False
		prev = collection[i]
	return True


def is_sorted_desc(collection):
	"""Checks if given collection is sorted (ascending)

	:param collection: Collection to check
	:return: True if is sorted
	"""
	if len(collection) <= 1:
		return True

	prev = collection[0]
	for i in range(1, len(collection)):
		if prev < collection[i]:
			return False
		prev = collection[i]
	return True


class CollectionNotSortedException(Exception):
	pass


def measure_exe_time(algo, collection):
	"""

	:param algo: Sorting function
	:param collection: Collection to sort
	:return: :raise:
	"""
	start = clock()
	algo(collection)
	stop = clock()
	#if not is_sorted_desc(collection):
	#	pass
		#raise CollectionNotSortedException
	return stop - start


def analyse_random_case(probe_sizes, algo):
	results = []

	for n in probe_sizes:
		coll = generate_random_sequence(n, 0, 10000)
		time = measure_exe_time(algo, coll)
		results.append(time)

	return results
