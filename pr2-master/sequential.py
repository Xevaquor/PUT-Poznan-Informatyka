from distance import word_distance
import codecs
import sys
import time

term = "miud"
dictname = 'malutki.txt'

if len(sys.argv) == 3:
    term = sys.argv[1]
    dictname = sys.argv[2]

def read_dictionary(filename):
    content = codecs.open(filename, mode='r', encoding='utf-8').read()
    return content.split()

print('Looking for {} in {}'.format(term, dictname))

words = read_dictionary(dictname)

start = time.perf_counter()

dict_size = len(words)
best_index = -1
best_distance = 9999999
best_match = term

for i, x in enumerate(words):

    d = word_distance(x, term)
    if d < best_distance:
        best_distance = d
        best_match = x
        best_index = i

stop = time.perf_counter()
print("FOUND: {} at {} with distance {}".format(best_match, best_index, best_distance))
print("Elapsed time {}s".format(stop-start))


