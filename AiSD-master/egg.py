import matplotlib.pyplot as plt
import merge_sort

from utils import *
from bubble_sort import bubble
from merge_sort import merge_sort, calle


# seq = generate_random_sequence(5000)
# print(seq)
# t = measure_exe_time(bubble, seq)
# print(seq)
# print(t)
#

#print (merge_sort([9,6,3,5,8,4,5,2,3,5,5,4,7,0]))
probes = range(0, 1001, 100)
# bubble = analyse_random_case(probes, bubble)
merge = analyse_random_case(probes, calle)
# r = []
# print(r)
# # print(seq[::-1])
#
# plt.plot(probes, bubble)
plt.plot(probes, merge)
plt.savefig('xd.png')
plt.show()
