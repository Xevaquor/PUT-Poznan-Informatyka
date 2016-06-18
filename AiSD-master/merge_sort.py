__author__ = 'Mateusz Bednarski'


def merge(left, right):
	size_l = len(left)
	size_r = len(right)
	axis_l = 0
	axis_r = 0

	out = []

	while axis_l < size_l or axis_r < size_r:
		#no elements left in left (we need to go deeper)
		if axis_l == size_l:
			out.append(right[axis_r])
			axis_r += 1
			continue
		#no elements left in right
		if axis_r == size_r:
			out.append(left[axis_l])
			axis_l += 1
			continue
		#select less (evil)
		if right[axis_r] <= left[axis_l]:
			out.append(right[axis_r])
			axis_r += 1
		else:
			out.append(left[axis_l])
			axis_l += 1

	return out

def calle(collection):
	sorted = merge_sort(collection)
	collection[:] = sorted[:]
	# for i in range(0, len(collection)):
	# 	collection[i] = sorted[i]

def merge_sort(collection):
	n = len(collection)
	if n <= 1:
		return collection
	pivot = n/2
	left = merge_sort(collection[pivot:])
	right = merge_sort(collection[:pivot])
	return merge(left, right)