import prettyplotlib as ppl
from prettyplotlib import brewer2mpl
import matplotlib.pyplot as plt
import numpy as np
#from analyzer import guard_percentages, sizes
import matplotlib.ticker as ticker
from matplotlib.colors import LogNorm
import pandas as pd

purples = brewer2mpl.get_map('Purples', 'Sequential', 9).mpl_colormap

data = pd.read_csv('clean.txt', sep=' ', header=None)
seq_times = np.array([43.05324205101351,
58.40454645099817,
72.48805438299314,
87.82189680699958,
105.97584470099537,
116.47462376701878,
144.88318312098272,
165.84237372799544,
176.9974813630106,
187.98173966401373,
203.43700645200443,
223.72902374199475])

print(data)
print(data.head())

processes = [2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 16, 18, 20, 24, 28, 33, 40]
raw = np.ones((12,19))
raw[:,:18] = data[2].reshape(12,18)
raw[:,18] = seq_times

vs_all = data[2][198:]
vs_comm = data[3][198:]
vs_diff = (vs_comm/(vs_all)).reshape((18))

X = np.linspace(2,14,18)

#raw = np.log(raw)

fig, ax = plt.subplots(1)

ax.set_xlabel('Liczba procesow')
ax.set_ylabel('Dlugosc slowa')
cb = ppl.pcolormesh(fig, ax, raw,
			   cmap=purples,
                  xticklabels = [2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 16, 18, 20, 24, 28, 33, 40]
                  ,
                  norm=LogNorm(vmin=raw.min(), vmax=raw.max())
                     )

#plt.plot(X, seq_times)

#ppl.pcolormesh(raw)
plt.show()

plt.clf()

plt.plot(processes, vs_diff)
#plt.xticks(processes, processes)
plt.xlabel('Liczba procesow')
plt.ylabel('Stosunek czasu komunikacji/przetwarzania [0;1]')

plt.clf()

sizes = range(2, 14)

for i in range(0, 19):
    c = color='red' if i == 18  else 'black'
    plt.plot(sizes[:-2], raw[:-2,i])
    
plt.xlabel('Dlugosc slowa')
plt.ylabel('Czas przetwarzania [s]')
#plt.legend()

plt.clf()
xd = list(range(len(processes)))

plt.bar(processes, vs_all-vs_comm, color='red', bottom=vs_comm, log=False)
plt.bar(processes, vs_comm, color='green', log=False)
plt.xlabel('Liczba procesow')
plt.ylabel('Czas wykonania [s]')
plt.show()