import os
import subprocess

hostfile = "power"
processes = [2]#, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 16, 18, 20, 24, 28, 33, 40]
words = ['xd',
         'fyć',
         'miud',
         'kułka',
         'wziąść',
         'wzglond',
         'otfieracz',
         'kąputerowy',
         'wyrafnowany',
         'metodologjia',
         'sgffihrgyuuiu',
         'nieposkromoiny',
         'wykwaliifkowaną']

with open('seq_res', 'a') as f:
	for w in words:
		for n in processes:
			#command = ["mpiexec", "-n", str(n), '-hostfile', hostfile, 'python3', 'distributed.py', 'malutki.txt',  w, 'xd']
			command = ["python3", "sequential.py", w, "slowa.txt"]
			result = subprocess.check_output(command)
			print("{} {} {}".format(w, n, str(result)))
			f.write	("{} {} {}\n".format(w, n, str(result)))
			f.flush()

