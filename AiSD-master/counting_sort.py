__author__ = 'Mateusz Bednarski'


def get_max_val(A):
	maxima = A[0]
	for x in A:
		if x > maxima:
			maxima = x
	return maxima

def counting_sort(collection):
	maxval = get_max_val(collection)
	occurences = [0] * (maxval + 1)
	for x in collection:
		occurences[x] += 1

	i = 0
	for y in range(maxval, 0, -1):
		for z in range(occurences[y]):
			collection[i] = y
			i += 1
if __name__ == '__main__':
	c = [2,2,6,9,8,5,5,6,5,4,1,2,6,5,7,5,9,6]
	counting_sort(c,9)
	print (c)

