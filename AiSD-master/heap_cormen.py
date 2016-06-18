__author__ = 'Mateusz Bednarski'


def parent(i):
	return i/2

def left(i):
	return 2*i

def right(i):
	return 2* i + 1

def MinHeapify(A, i):
	l = left(i)
	r = right(i)
	if l <= heap_size and A[l] < A[i]:
		largest = l
	else:
		largest = i
	if r <= heap_size and A[largest] > A[r]:
		largest = r
	if largest != i:
		A[i], A[largest] = A[largest], A[i]
		MinHeapify(A, largest)




def BuildMinHeap(A, n):
	heap_size = n
	for i in (n/2, 0, -1):
		MinHeapify(A, i)

heap_size = 10


def Heapsort(A, n):
	A.insert(0, 0)
	BuildMinHeap(A, n)
	for i in range(n , 1, -1):
		A[1], A[i] = A[i], A[1]
		heap_size -= 1
		MinHeapify(A, 1)

dd = [5,3,6,4,1]
Heapsort(dd, len(dd))
print dd