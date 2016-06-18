#na pdostawie sedgewicka

def shell_sort(a):
	n = len(a)
	h = 1
	while h < n/3:
		h = 3 * h + 1
	while h >= 1:
		for i in range(h, n):
			j = i
			while j >= h and a[j] > a[j-h]:
				a[j], a[j-h] = a[j-h], a[j]
				j -= h
		h = h/3



if __name__ == '__main__':

	dd = [4, 3, 6, 5, 4, -10, 15, -45, 3, 8]
	shell_sort(dd)
	print dd