__author__ = 'Mateusz Bednarski'


from counting_sort import counting_sort
from qsort import QuickSort
from qsort_iter import QuickSortIterative
from heap_sort import heap_sort
from shell import shell_sort
from utils import measure_exe_time, is_sorted_desc
from generators import *


def menu_algo():
	print ( "Wybierz algorytm:\n"
			"0 Counting sort\n"
			"1 QSort\n"
			"2 Qsort iteracyjnie\n"
			"3 Heap sort\n"
			"4 Shell sort\n")
	return int(raw_input())

def menu_size():
	return int(raw_input("Wielkosc danych "))

def menu_generator():
	print ( "Wybierz generator:\n"
			"0 rosnaco\n"
			"1 malejaco\n"
			"2 V-ksztaltnie\n"
			"3 losowo\n")
	return int(raw_input())

if __name__ == '__main__':
	algo = menu_algo()
	size = menu_size()
	generator = menu_generator()

	algos = [counting_sort, QuickSort, QuickSortIterative, heap_sort, shell_sort]
	generators = [generate_ascending_sequence,
				  generate_descending_sequence,
				  generate_v_sequence,
				  generate_random_sequence]

	seq = generators[generator](size)

	if size < 11:
		print "Sekwencja wejsciowa: ", seq

	perf = measure_exe_time(algos[algo], seq)

	if size < 11:
		print "Sekwencja wyjsciowa: ", seq

	print "Czas wykonania: ", perf
	print is_sorted_desc(seq)

	raw_input()



