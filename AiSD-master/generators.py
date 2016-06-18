from random import randint

__author__ = 'Mateusz Bednarski'


def generate_random_sequence(size, min_val=0, max_val=100000):
	seq = []
	for i in range(size):
		seq.append(randint(min_val, max_val))
	return seq


def generate_ascending_sequence(size, min_val=0, max_val=100000):
	seq = generate_random_sequence(size, min_val, max_val)
	seq.sort()
	return seq

def generate_descending_sequence(size, min_val=0, max_val=100000):
	seq = generate_random_sequence(size, min_val, max_val)
	seq.sort()
	seq.reverse()
	return seq

def generate_v_sequence(size, min_val=0, max_val=100000):
	a = generate_descending_sequence(size / 2, min_val, max_val)
	b = generate_ascending_sequence(size - size / 2, min_val, max_val)
	return a + b

if __name__ == '__main__':
	print generate_descending_sequence(10)
	print generate_ascending_sequence(10)
	print generate_random_sequence(10)
	print generate_v_sequence(10)