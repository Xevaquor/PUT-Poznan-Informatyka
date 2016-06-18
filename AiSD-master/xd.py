__author__ = 'Mateusz Bednarski'

from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from numpy import *
from utils import measure_exe_time
from generators import *
from counting_sort import counting_sort

def f(n, b):
	results = []
	for i in range(1):
		data = generate_random_sequence(n, max_val = b)
		perf = measure_exe_time(counting_sort, data)
		results.append(perf)
	return mean(results)


probes = [1000,10000,100000,200000,300000,400000]
b_param = [10000,50000,100000,150000, 175000]


phi_m = linspace(0, 2*pi, 100)
phi_p = linspace(0, 2*pi, 100)

X,Y = meshgrid(probes, b_param)
#Z = f(probes, b_param)
Z = zeros([len(probes),len(b_param)])

for n in range(0, len(probes)):
	for b in range(0, len(b_param)):
		Z[n] = f(probes[n], b_param[b])

fig, ax = plt.subplots()

p = ax.pcolor(X/(2*pi), Y/(2*pi), Z, vmin=abs(Z).min(), vmax=abs(Z).max())
cb = fig.colorbar(p, ax=ax)
plt.xticks(probes)
plt.yticks(b_param)
plt.show()
